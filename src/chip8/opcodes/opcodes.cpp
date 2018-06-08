#include "Opcodes.h"
#include <stdlib.h>
#include <string>

#define NIBBLE_X GetNibble(0xF00, 8)
#define NIBBLE_Y GetNibble(0xF0, 4)

namespace Chips {
	Opcodes::Opcodes(Cpu & c, Memory & m, Keypad & k):
			_cpu(c),
			_memory(m),
			_keypad(k)
		{
	
		_curOpcode = 0;
		std::fill(opcode0Table, opcode0Table + 256, &Opcodes::_0NNN);
		opcode0Table[0xE0] = &Opcodes::_00E0;
		opcode0Table[0xEE] = &Opcodes::_00EE;
	
		std::fill(opcode8Table, opcode8Table + 16, &Opcodes::opNULL);
		opcode8Table[0x0] = &Opcodes::_8XY0;
		opcode8Table[0x1] = &Opcodes::_8XY1;
		opcode8Table[0x2] = &Opcodes::_8XY2;
		opcode8Table[0x3] = &Opcodes::_8XY3;
		opcode8Table[0x4] = &Opcodes::_8XY4;
		opcode8Table[0x5] = &Opcodes::_8XY5;
		opcode8Table[0x6] = &Opcodes::_8XY6;
		opcode8Table[0x7] = &Opcodes::_8XY7;
		opcode8Table[0xE] = &Opcodes::_8XYE;
	
		std::fill(opcode9Table, opcode9Table + 16, &Opcodes::opNULL);
		opcode9Table[0x0] = &Opcodes::_9XY0;

		std::fill(opcodeETable, opcodeETable + 256, &Opcodes::opNULL);
		opcodeETable[0x9E] = &Opcodes::_EX9E;
		opcodeETable[0xA1] = &Opcodes::_EXA1;

		std::fill(opcodeFTable, opcodeFTable + 256, &Opcodes::opNULL);
		opcodeFTable[0x07] = &Opcodes::_FX07;
		opcodeFTable[0x0A] = &Opcodes::_FX0A;
		opcodeFTable[0x15] = &Opcodes::_FX15;
		opcodeFTable[0x18] = &Opcodes::_FX18;
		opcodeFTable[0x1E] = &Opcodes::_FX1E;
		opcodeFTable[0x29] = &Opcodes::_FX29;
		opcodeFTable[0x33] = &Opcodes::_FX33;
		opcodeFTable[0x55] = &Opcodes::_FX55;
		opcodeFTable[0x65] = &Opcodes::_FX65;
	}
	
	inline WORD Opcodes::GetNibble(WORD mask, BYTE shift) {
		return (_curOpcode & mask) >> shift;	
	}
	
	void Opcodes::Execute(WORD op) {
		_curOpcode = op;	
	
		(this->*opcodesTable[GetNibble(0xF000, 12)])();
	}
	
	void Opcodes::op_0() {
		(this->*opcode0Table[GetNibble(0xFF)])();
	}
		
	void Opcodes::op_8() {
		(this->*opcode8Table[GetNibble(0xF)])();
	}
		
	void Opcodes::op_9() {
		(this->*opcode9Table[GetNibble(0xF)])();
	}
	
	void Opcodes::op_E() {
		(this->*opcodeETable[GetNibble(0xFF)])();
	}
		
	void Opcodes::op_F() {
		(this->*opcodeFTable[GetNibble(0xFF)])();
	}
	
	void Opcodes::opNULL() { //Todo
		//errorCode = 2;
	}
	
	void Opcodes::_00E0() { //CLS: Clears the screen
		_memory.FillGfx(GFX_SIZE, 0);
		_memory.SetDrawFlag(true);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_00EE() { //Returns from a subroutine
		_cpu.DecSP();
		_cpu.SetPC(_cpu.GetStack(_cpu.GetSP()));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_0NNN() { //Execute machine language subrourine at address NNN
		//Todo
		opNULL();
	}
	
	void Opcodes::_1NNN() { //Jumps to address NNN
		_cpu.SetPC(GetNibble(0xFFF));
	}
	
	void Opcodes::_2NNN() { //Calls subroutine at NNN
		_cpu.SetStack(_cpu.GetSP(), _cpu.GetPC());
		_cpu.IncSP();
		_cpu.SetPC(GetNibble(0xFFF));
	}
	
	void Opcodes::_3XKK() { //Skips the next instruction if VX equals NN
		if(_cpu.GetV(NIBBLE_X) == GetNibble(0xFF))
			_cpu.IncPC(4);
		else
			_cpu.IncPC(2);
	}
	
	void Opcodes::_4XKK() { //Skips the next instruction if VX doesn't equal NN
		if(_cpu.GetV(NIBBLE_X) != GetNibble(0xFF))
			_cpu.IncPC(4);
		else
			_cpu.IncPC(2);
	}
	
	void Opcodes::_5XY0() { //Skips the next instruction if VX equals VY
		if(_cpu.GetV(NIBBLE_X) == _cpu.GetV(GetNibble(0xF0, 4)))
			_cpu.IncPC(4);
		else
			_cpu.IncPC(2);
	}
	
	void Opcodes::_6XKK() { //Sets VX to NN
		_cpu.SetV(NIBBLE_X, GetNibble(0xFF));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_7XKK() { //Adds NN to VX
		_cpu.AddV(NIBBLE_X, GetNibble(0xFF));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY0() { //Sets VX to the value of VY
		_cpu.SetV(NIBBLE_X, _cpu.GetV(NIBBLE_Y));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY1() { //Sets VX to "VX OR VY"
		_cpu.OrV(NIBBLE_X, NIBBLE_Y);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY2() { //Sets VX to "VX AND VY"
		_cpu.AndV(NIBBLE_X, NIBBLE_Y);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY3() { //Sets VX to "VX XOR VY"
		_cpu.XorV(NIBBLE_X, NIBBLE_Y);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY4() { //Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't					
		if(_cpu.GetV(NIBBLE_Y) > (0xFF - _cpu.GetV(NIBBLE_X))) 
			_cpu.SetV(0xF, 1); //carry
		else 
			_cpu.SetV(0xF, 0);					
		_cpu.AddV(NIBBLE_X, _cpu.GetV(NIBBLE_Y));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY5() {  //VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
		if(_cpu.GetV(NIBBLE_Y) > _cpu.GetV(NIBBLE_X)) 
			_cpu.SetV(0xF, 0); // there is a borrow
		else 
			_cpu.SetV(0xF, 1);					
		_cpu.SubV(NIBBLE_X, _cpu.GetV(NIBBLE_Y));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY6() { //Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift
		_cpu.SetV(0xF, _cpu.GetV(NIBBLE_X) & 0x1);
		_cpu.SetV(NIBBLE_X, _cpu.GetV(NIBBLE_X) >> 1);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XY7() { //Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
		if(_cpu.GetV(NIBBLE_X) > _cpu.GetV(NIBBLE_Y))	// VY-VX
			_cpu.SetV(0xF, 0); // there is a borrow
		else
			_cpu.SetV(0xF, 1);
		_cpu.SetV(NIBBLE_X, _cpu.GetV(NIBBLE_Y) - _cpu.GetV(NIBBLE_X));				
		_cpu.IncPC(2);
	}
	
	void Opcodes::_8XYE() { //Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift
		_cpu.SetV(0xF, _cpu.GetV(NIBBLE_X) >> 7);
		_cpu.SetV(NIBBLE_X, _cpu.GetV(NIBBLE_X) << 1);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_9XY0() { //Skips the next instruction if VX doesn't equal VY
		if(_cpu.GetV(NIBBLE_X) != _cpu.GetV(NIBBLE_Y))
			_cpu.IncPC(4);
		else
			_cpu.IncPC(2);
	}
	
	void Opcodes::_ANNN() { //Sets I to the address NNN
		_cpu.SetI(_curOpcode & 0xFFF);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_BNNN() { //Jumps to the address NNN plus V0.
		_cpu.SetPC((_curOpcode & 0xFFF) + _cpu.GetV(0));
	}
	
	void Opcodes::_CXKK() { //Sets VX to a random number and NN.
		_cpu.SetV(NIBBLE_X, (rand() % 0xFF) & (_curOpcode & 0xFF));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_DXYN() { //Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as 
		 //bit-coded (with the most significant bit of each byte displayed on the left) starting from memory location I; I value doesn't 
		 //change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to
		 //unset when the sprite is drawn, and to 0 if that doesn't happen.
		WORD height = _curOpcode & 0x000F;
		WORD pixel;

		_cpu.SetV(0xF, 0);
		for (int yline = 0; yline < height; yline++)
		{
			pixel = _memory.GetMemory(_cpu.GetI() + yline);
			for(int xline = 0; xline < 8; xline++)
			{
				if((pixel & (0x80 >> xline)) != 0)
				{
					if(_memory.GetGfx(_cpu.GetV(NIBBLE_X) + xline + ((_cpu.GetV(NIBBLE_Y) + yline) * 64)) == 1)
					{
						_cpu.SetV(0xF, 1);                                    
					}
					_memory.ToggleGfx(_cpu.GetV(NIBBLE_X) + xline + ((_cpu.GetV(NIBBLE_Y) + yline) * 64));
				}
			}
		}
						
		_memory.SetDrawFlag(true);			
		_cpu.IncPC(2);
	}
	
	void Opcodes::_EX9E() { //Skips the next instruction if the key stored in VX is pressed
		if(_keypad.GetKey(_cpu.GetV(NIBBLE_X)) != 0)
			_cpu.IncPC(4);
		else
			_cpu.IncPC(2);
	}
	
	void Opcodes::_EXA1() { //Skips the next instruction if the key stored in VX isn't pressed
		if(_keypad.GetKey(_cpu.GetV(NIBBLE_X)) == 0)
			_cpu.IncPC(4);
		else
			_cpu.IncPC(2);
	}
	
	void Opcodes::_FX07() { //Sets VX to the value of the delay timer
		_cpu.SetV(NIBBLE_X, _cpu.GetDelayTimer());
		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX0A() { //A key press is awaited, and then stored in VX
		bool keyPress = false;

		for(int i = 0; i < 16; ++i) {
			if(_keypad.GetKey(i) != 0) {
				_cpu.SetV(NIBBLE_X, i);
				keyPress = true;
			}
		}

		// If we didn't received a keypress, skip this cycle and try again.
		if(!keyPress)						
			return;

		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX15() { //Sets the delay timer to VX
		_cpu.SetDelayTimer(_cpu.GetV(NIBBLE_X));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX18() { //Sets the sound timer to VX
		_cpu.SetSoundTimer(_cpu.GetV(NIBBLE_X));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX1E() { //Adds VX to I
		if(_cpu.GetI() + _cpu.GetV(NIBBLE_X) > 0xFFF)	// VF is set to 1 when range overflow (I+VX>0xFFF), and 0 when there isn't.
			_cpu.SetV(0xF, 1);
		else
			_cpu.SetV(0xF, 0);
		_cpu.SetI(_cpu.GetI() + _cpu.GetV(NIBBLE_X));
		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX29() { //Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font
		_cpu.SetI(_cpu.GetV(NIBBLE_X) * 0x5);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX33() { //Stores the Binary-coded decimal representation of VX at the addresses I, I plus 1, and I plus 2
		_memory.SetMemory(_cpu.GetI(), _cpu.GetV(NIBBLE_X) / 100);
		_memory.SetMemory(_cpu.GetI() + 1, (_cpu.GetV(NIBBLE_X) / 10) % 10);
		_memory.SetMemory(_cpu.GetI() + 2, (_cpu.GetV(NIBBLE_X) % 100) % 10);				
		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX55() { //Stores V0 to VX in memory starting at address I					
		for (int i = 0; i <= NIBBLE_X; ++i)
			_memory.SetMemory(_cpu.GetI() + i, _cpu.GetV(i));	

		// On the original interpreter, when the operation is done, I = I + X + 1.
		_cpu.SetI(_cpu.GetI() + NIBBLE_X + 1);
		_cpu.IncPC(2);
	}
	
	void Opcodes::_FX65() { //Fills V0 to VX with values from memory starting at address I					
		for (int i = 0; i <= NIBBLE_X; ++i)
			_cpu.SetV(i, _memory.GetMemory(_cpu.GetI() + i));			

		// On the original interpreter, when the operation is done, I = I + X + 1.
		_cpu.SetI(_cpu.GetI() + NIBBLE_X + 1);
		_cpu.IncPC(2);
	}
}	