#include "cpu.h"
#include <iostream>

namespace Chips {
	Cpu::Cpu() {
		_PC = PC_START_ADDR;
		_I = 0;
		std::fill(_V, _V + V_REGISTER_COUNT, 0);
		
		_SP = 0;
		std::fill(_stack, _stack + STACK_LEVEL_COUNT, 0);
		
		_timerDelay = 0;
		_timerSound = 0;
	}
	
	WORD Cpu::GetPC() {
		return _PC;
	}

	void Cpu::SetPC(WORD value) {
		_PC = value;
	}

	void Cpu::IncPC(WORD step=1) {
		_PC += step;
	}

	BYTE Cpu::GetV(WORD index) {
		return _V[index];
	}

	void Cpu::SetV(WORD index, BYTE value) {
		_V[index] = value;
	}

	void Cpu::AddV(WORD index, BYTE value) {
		_V[index] += value;
	}

	void Cpu::SubV(WORD index, BYTE value) {
		_V[index] -= value;
	}

	void Cpu::AndV(WORD index, BYTE value) {
		_V[index] &= value;
	}

	void Cpu::OrV(WORD index, BYTE value) {
		_V[index] |= value;
	}

	void Cpu::XorV(WORD index, BYTE value) {
		_V[index] ^= value;
	}

	WORD Cpu::GetI() {
		return _I;
	}

	void Cpu::SetI(WORD value) {
		_I = value;
	}

	WORD Cpu::GetStack(WORD index) {
		return _stack[index];
	}

	void Cpu::SetStack(WORD index, WORD value) {
		_stack[index] = value;
	}
	
	WORD Cpu::GetSP() {
		return _SP;
	}

	void Cpu::IncSP() {
		++_SP;
	}

	void Cpu::DecSP() {
		--_SP;
	}
	
	BYTE Cpu::GetDelayTimer() {
		return _timerDelay;
	}

	void Cpu::SetDelayTimer(BYTE value) {
		_timerDelay = value;
	}
	
	void Cpu::DecDelayTimer() {
		--_timerDelay;
	}

	BYTE Cpu::GetSoundTimer() {
		return _timerSound;
	}

	void Cpu::SetSoundTimer(BYTE value) {
		_timerSound = value;
	}
	
	void Cpu::DecSoundTimer() {
		--_timerSound;
	}
}
