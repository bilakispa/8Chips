#ifndef CPU_H
#define CPU_H
#include "definitions.h"

namespace Chips {
	class Cpu {
		WORD _PC; //Program Counter
		WORD _I; //Index register
		BYTE _V[V_REGISTER_COUNT]; //V0-VF 8bit registers

		WORD _stack[STACK_LEVEL_COUNT]; //A 16-level stack
		WORD _SP; //The stack pointer
		
		BYTE _timerDelay; //The delay timer
		BYTE _timerSound; //The sound timer
	public:
		Cpu();
	
		WORD GetPC();
		void SetPC(WORD);
		void IncPC(WORD);
		
		BYTE GetV(WORD);
		void SetV(WORD, BYTE);
		void AddV(WORD, BYTE);
		void SubV(WORD, BYTE);
		void AndV(WORD, BYTE);
		void OrV(WORD, BYTE);
		void XorV(WORD, BYTE);
		
		WORD GetI();
		void SetI(WORD);
		
		WORD GetStack(WORD);
		void SetStack(WORD, WORD);
		
		WORD GetSP();
		void IncSP();
		void DecSP();
		
		BYTE GetDelayTimer();
		void SetDelayTimer(BYTE);
		void DecDelayTimer();
		BYTE GetSoundTimer();
		void SetSoundTimer(BYTE);
		void DecSoundTimer();
	};
}
#endif