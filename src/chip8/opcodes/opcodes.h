#ifndef OPCODES_H
#define OPCODES_H
#include <functional>
#include "chip8/cpu/cpu.h"
#include "chip8/memory/memory.h"
#include "chip8/keypad/keypad.h"
#include "chip8/definitions.h"
#include "log.h"

namespace Chips {
	class Opcodes {
		WORD _curOpcode;
		Cpu &_cpu;
		Memory &_memory;
		Keypad &_keypad;
	
		typedef void (Opcodes::*OpcodePointer) ();
		OpcodePointer opcodesTable[16] = {
			&Opcodes::op_0, &Opcodes::_1NNN, &Opcodes::_2NNN, &Opcodes::_3XKK,
			&Opcodes::_4XKK, &Opcodes::_5XY0, &Opcodes::_6XKK, &Opcodes::_7XKK,
			&Opcodes::op_8, &Opcodes::op_9, &Opcodes::_ANNN, &Opcodes::_BNNN,
			&Opcodes::_CXKK, &Opcodes::_DXYN, &Opcodes::op_E, &Opcodes::op_F
		};
		OpcodePointer opcode0Table[256];
		OpcodePointer opcode8Table[16];
		OpcodePointer opcode9Table[16];
		OpcodePointer opcodeETable[256];
		OpcodePointer opcodeFTable[256];

		inline WORD GetNibble(WORD, BYTE shift=0);
		void opNULL(); void op_0(); void op_8(); void op_9(); void op_E(); void op_F();
		void _00E0(); void _00EE(); void _0NNN();
		void _1NNN();
		void _2NNN();
		void _3XKK();
		void _4XKK();
		void _5XY0();
		void _6XKK();
		void _7XKK();
		void _8XY0(); void _8XY1(); void _8XY2(); void _8XY3(); void _8XY4(); void _8XY5(); void _8XY6(); void _8XY7(); void _8XYE();
		void _9XY0();
		void _ANNN();
		void _BNNN();
		void _CXKK();
		void _DXYN();
		void _EX9E(); void _EXA1();
		void _FX07(); void _FX0A(); void _FX15(); void _FX18(); void _FX1E(); void _FX29(); void _FX33(); void _FX55(); void _FX65();

	public:
		Opcodes(Cpu &, Memory &, Keypad &);
	
		void Execute(WORD);
	};
}
#endif