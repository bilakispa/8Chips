#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <cstdint>

namespace Chips {
	typedef uint8_t BYTE;
	typedef uint16_t WORD;

	const int PC_START_ADDR = 0x200;
	const int V_REGISTER_COUNT = 16;
	const int STACK_LEVEL_COUNT = 16;

	const int MEMORY_SIZE = 0x1000;
	const int MEMORY_DATA_START = 0x200;

	const int GFX_WIDTH = 64;
	const int GFX_HEIGHT = 32;
	const int GFX_SIZE = GFX_WIDTH * GFX_HEIGHT;
	
	const int FONT_SET_SIZE = 80;
	const BYTE FONT_SET[] = 
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
	
	const int KEYPAD_SIZE = 16;
}
#endif
