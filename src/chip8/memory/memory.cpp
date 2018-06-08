#include "memory.h"
#include <algorithm>

namespace Chips {
	Memory::Memory() {
		std::fill(_mem, _mem + MEMORY_SIZE, 0);
		std::copy(FONT_SET, FONT_SET + FONT_SET_SIZE, _mem);
		std::fill(_gfx, _gfx + GFX_SIZE, 0);
		_drawFlag = true; //clear display
	}
	
	BYTE Memory::GetMemory(WORD index) {
	 return _mem[index];
	}
	
	void Memory::SetMemory(WORD index, BYTE value) {
		_mem[index] = value;
	}
	
	BYTE Memory::GetGfx(WORD index) {
		return _gfx[index];
	}
	
	void Memory::ToggleGfx(WORD index) {
		_gfx[index] ^= 1;
	}
	
	void Memory::FillGfx(unsigned int size, BYTE value) {
		std::fill(_gfx, _gfx + size, value);
	}
	
	bool Memory::GetDrawFlag() {
		return _drawFlag;
	}
	
	void Memory::SetDrawFlag(bool value) {
		_drawFlag = value;
	}
}
