#ifndef MEMORY_H
#define MEMORY_H
#include "chip8/definitions.h"

namespace Chips {
	class Memory {
		BYTE _mem[MEMORY_SIZE]; //Memory 4k byte
		BYTE _gfx[GFX_SIZE]; //The display native resolution (ammount of pixels: 2048)
		bool _drawFlag;
	public:
		Memory();
		
		BYTE GetMemory(WORD);
		void SetMemory(WORD, BYTE);
		
		BYTE GetGfx(WORD);
		void ToggleGfx(WORD);
		void FillGfx(unsigned int, BYTE);
		
		bool GetDrawFlag();
		void SetDrawFlag(bool);
	};
}
#endif