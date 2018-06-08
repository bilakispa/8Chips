#ifndef KEYPAD_H
#define KEYPAD_H
#include "chip8/definitions.h"

namespace Chips {
	class Keypad {
		BYTE _key[KEYPAD_SIZE];
		
	public:
		Keypad();
		BYTE GetKey(BYTE);
		void SetKey(BYTE, BYTE);
	};
}
#endif