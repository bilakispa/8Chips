#include "chip8.h"
#include <iostream>
#include <time.h> //TODO: CHANGE THIS IF NEEDED
#include <windows.h>

unsigned char chip8_fontset[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, //0
	0x20, 0x60, 0x20, 0x20, 0x70, //1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
	0x90, 0x90, 0xF0, 0x10, 0x10, //4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
	0xF0, 0x10, 0x20, 0x40, 0x40, //7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
	0xF0, 0x90, 0xF0, 0x90, 0x90, //A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
	0xF0, 0x80, 0x80, 0x80, 0xF0, //C
	0xE0, 0x90, 0x90, 0x90, 0xE0, //D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
	0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

Chip8::Chip8() {
	pc = 0x200; //clear to start address program
	I = 0; //clear index register
	opcode = 0; //clear opcode
	sp = 0; //stack pointer
	drawFlag = true; //clear screen

	for (int i = 0; i<16; i++) { //clear stack
		stack[i] = 0;
	}

	for (int i = 0; i<4096; i++) //clear memory
		memory[i] = 0;

	for (int i = 0; i < 80; ++i) // Load fontset
		memory[i] = chip8_fontset[i];

	for (int i = 0; i<16; i++) { //clear V0-VF registers
		V[i] = 0;
	}

	for (int i = 0; i<2048; i++) { //clear display
		gfx[i] = 0;
	}

	for (int i = 0; i<16; i++) { //clear keypad 
		key[i] = 0;
	}

	//clear timers
	delay_timer = 0;
	sound_timer = 0;

	srand((unsigned int)time(NULL)); //Randomize

	int errorCode = 0;
}

void Chip8::emulateCycle() {
	//reset errorCode
	errorCode = 0;

	//Fetch opcode
	opcode = memory[pc] << 8 | memory[pc + 1];

	//Temporary store VX,VY
	X = (opcode & 0x0F00) >> 8;
	Y = (opcode & 0x00F0) >> 4;

	//Decode and Excecute opcode
	switch (opcode & 0xF000) {
	case 0x0000: //0???
#pragma region switch(opcode & 0x00FF)
		switch (opcode & 0x000F) {
		case 0x0000: //00E0: Clears the screen
			for (int i = 0; i< 2048; i++) {
				gfx[i] = 0x0;
			}
			drawFlag = true;
			pc += 2;
			break;
		case 0x000E: //00EE: Returns from a subroutine
			--sp;
			pc = stack[sp];
			pc += 2;
			break;
		default:
			errorCode = 1;
		}
#pragma endregion
		break;
	case 0x1000: //1NNN: Jumps to address NNN
		pc = opcode & 0x0FFF;
		break;
	case 0x2000: //2NNN: Calls subroutine at NNN
		stack[sp] = pc;
		++sp;	
		pc = opcode & 0x0FFF;
		break;
	case 0x3000: //3XNN: Skips the next instruction if VX equals NN
			if(V[X] == (opcode & 0x00FF))
				pc += 4;
			else
				pc += 2;
		break;
	case 0x4000: //4XNN: Skips the next instruction if VX doesn't equal NN
		if(V[X] != (opcode & 0x00FF))
				pc += 4;
			else
				pc += 2;
		break;
	case 0x5000: //5XY0: Skips the next instruction if VX equals VY
		if(V[X] == V[Y])
				pc += 4;
			else
				pc += 2;
		break;
	case 0x6000: //6XNN: Sets VX to NN
		V[X] = opcode & 0x00FF;
			pc += 2;
		break;
		break;
	case 0x7000: //7XNN: Adds NN to VX
		V[X] += opcode & 0x00FF;
			pc += 2;
		break;
	case 0x8000: //8XY?
		switch (opcode & 0x000F) {
		case 0x0000: // 0x8XY0: Sets VX to the value of VY
					V[X] = V[Y];
					pc += 2;
				break;

				case 0x0001: // 0x8XY1: Sets VX to "VX OR VY"
					V[X] |= V[Y];
					pc += 2;
				break;

				case 0x0002: // 0x8XY2: Sets VX to "VX AND VY"
					V[X] &= V[Y];
					pc += 2;
				break;

				case 0x0003: // 0x8XY3: Sets VX to "VX XOR VY"
					V[X] ^= V[Y];
					pc += 2;
				break;

				case 0x0004: // 0x8XY4: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't					
					if(V[Y] > (0xFF - V[X])) 
						V[0xF] = 1; //carry
					else 
						V[0xF] = 0;					
					V[X] += V[Y];
					pc += 2;					
				break;

				case 0x0005: // 0x8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
					if(V[Y] > V[X]) 
						V[0xF] = 0; // there is a borrow
					else 
						V[0xF] = 1;					
					V[X] -= V[Y];
					pc += 2;
				break;

				case 0x0006: // 0x8XY6: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift
					V[0xF] = V[X] & 0x1;
					V[X] >>= 1;
					pc += 2;
				break;

				case 0x0007: // 0x8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
					if(V[X] > V[Y])	// VY-VX
						V[0xF] = 0; // there is a borrow
					else
						V[0xF] = 1;
					V[X] = V[Y] - V[X];				
					pc += 2;
				break;

				case 0x000E: // 0x8XYE: Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift
					V[0xF] = V[X] >> 7;
					V[X] <<= 1;
					pc += 2;
		default:
			errorCode = 2;
		}
		break;
	case 0x9000: //9XY0: Skips the next instruction if VX doesn't equal VY
			if(V[X] != V[Y])
				pc += 4;
			else
				pc += 2;
		break;
	case 0xA000: //ANNN: Sets I to the address NNN
		I = opcode & 0x0FFF;
			pc += 2;
		break;
	case 0xB000: //BNNN: Jumps to the address NNN plus V0.
		pc = (opcode & 0x0FFF) + V[0];
		break;
	case 0xC000: //CXNN: Sets VX to a random number and NN.
		V[X] = (rand() % 0xFF) & (opcode & 0x00FF);
			pc += 2;
		break;
	case 0xD000: //DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as 
				 //bit-coded (with the most significant bit of each byte displayed on the left) starting from memory location I; I value doesn't 
				 //change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to
				 //unset when the sprite is drawn, and to 0 if that doesn't happen.
	{
			unsigned short height = opcode & 0x000F;
			unsigned short pixel;

			V[0xF] = 0;
			for (int yline = 0; yline < height; yline++)
			{
				pixel = memory[I + yline];
				for(int xline = 0; xline < 8; xline++)
				{
					if((pixel & (0x80 >> xline)) != 0)
					{
						if(gfx[(V[X] + xline + ((V[Y] + yline) * 64))] == 1)
						{
							V[0xF] = 1;                                    
						}
						gfx[V[X] + xline + ((V[Y] + yline) * 64)] ^= 1;
					}
				}
			}
						
			drawFlag = true;			
			pc += 2;
	}
	break;
	case 0xE000: //EX?? 
		switch (opcode & 0x00FF) {
			case 0x009E: // EX9E: Skips the next instruction if the key stored in VX is pressed
					if(key[V[X]] != 0)
						pc += 4;
					else
						pc += 2;
				break;
				
				case 0x00A1: // EXA1: Skips the next instruction if the key stored in VX isn't pressed
					if(key[V[X]] == 0)
						pc += 4;
					else
						pc += 2;
				break;
		default:
			errorCode = 3;
		}
		break;
	case 0xF000: //FX??
		switch (opcode & 0x00FF) {
		case 0x0007: // FX07: Sets VX to the value of the delay timer
					V[X] = delay_timer;
					pc += 2;
				break;
								
				case 0x000A: // FX0A: A key press is awaited, and then stored in VX		
				{
					bool keyPress = false;

					for(int i = 0; i < 16; ++i)
					{
						if(key[i] != 0)
						{
							V[X] = i;
							keyPress = true;
						}
					}

					// If we didn't received a keypress, skip this cycle and try again.
					if(!keyPress)						
						return;

					pc += 2;					
				}
				break;
				
				case 0x0015: // FX15: Sets the delay timer to VX
					delay_timer = V[X];
					pc += 2;
				break;

				case 0x0018: // FX18: Sets the sound timer to VX
					sound_timer = V[X];
					pc += 2;
				break;

				case 0x001E: // FX1E: Adds VX to I
					if(I + V[X] > 0xFFF)	// VF is set to 1 when range overflow (I+VX>0xFFF), and 0 when there isn't.
						V[0xF] = 1;
					else
						V[0xF] = 0;
					I += V[X];
					pc += 2;
				break;

				case 0x0029: // FX29: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font
					I = V[X] * 0x5;
					pc += 2;
				break;

				case 0x0033: // FX33: Stores the Binary-coded decimal representation of VX at the addresses I, I plus 1, and I plus 2
					memory[I]     = V[X] / 100;
					memory[I + 1] = (V[X] / 10) % 10;
					memory[I + 2] = (V[X] % 100) % 10;					
					pc += 2;
				break;

				case 0x0055: // FX55: Stores V0 to VX in memory starting at address I					
					for (int i = 0; i <= (X); ++i)
						memory[I + i] = V[i];	

					// On the original interpreter, when the operation is done, I = I + X + 1.
					I += (X) + 1;
					pc += 2;
				break;

				case 0x0065: // FX65: Fills V0 to VX with values from memory starting at address I					
					for (int i = 0; i <= (X); ++i)
						V[i] = memory[I + i];			

					// On the original interpreter, when the operation is done, I = I + X + 1.
					I += (X) + 1;
					pc += 2;
				break;
		default:
			errorCode = 4;
		}
		break;
	default:
		errorCode = 5;
	}

	// Update timers
	if (delay_timer > 0)
		--delay_timer;

	if (sound_timer > 0) {
		if (sound_timer == 1)
			Beep(440, 200);
		--sound_timer;
	}
}

void Chip8::setMemoryByte(int i, unsigned char value) {
	memory[i] = value;
}

bool Chip8::getDrawFlag() {
	return drawFlag;
}

void Chip8::setDrawFlag(bool set) {
	drawFlag = set;
}

int Chip8::getOpcode() {
	return opcode;
}