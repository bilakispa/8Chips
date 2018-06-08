#ifndef CHIP8_H
#define CHIP8_H
#include <string>
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "keypad/keypad.h"
#include "opcodes/opcodes.h"
#include "definitions.h"

namespace Chips {	
	class Chip8 {
	private:	
		bool isRunning;

		WORD _curOpcode; //2-byte long opcode

		Cpu _cpu;
		Memory _memory;
		Keypad _keypad;
		Opcodes _opcodes;
	
	public:
		int errorCode;

		Chip8();
		~Chip8();
		bool LoadRom(const std::string &);
		void Step();
		bool IsRunning();
		WORD GetOpcode();
		void SetOpcode(WORD);
		BYTE GetKey(WORD);
		void SetKey(WORD, BYTE);
	};
}
#endif