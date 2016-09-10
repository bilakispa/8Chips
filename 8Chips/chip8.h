class Chip8 {
private:
	unsigned char memory[4096]; //Memory 4k byte

	unsigned char V[16]; //V0-VF 1 byte registers
	unsigned short pc; //Program counter
	unsigned short I; //Index register
	unsigned short opcode; //2-byte long opcode

	unsigned short stack[16]; //A 16-level stack
	unsigned short sp; //The stack pointer

	unsigned char delay_timer; //The delay timer
	unsigned char sound_timer; //The sound timer

							   //The VX,VY temp variables
	unsigned char X;
	unsigned char Y;

	//Draw flag= when to draw screen
	bool drawFlag;
public:
	unsigned char gfx[64 * 32]; //The display resolution (ammount of pixels: 2048)
	unsigned char key[16]; //The keyboard

	int errorCode;

	Chip8();
	void emulateCycle();
	void setMemoryByte(int, unsigned char);
	bool getDrawFlag();
	void setDrawFlag(bool);
	int getOpcode();
};
