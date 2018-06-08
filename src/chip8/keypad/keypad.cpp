#include "keypad.h"
#include <algorithm>

namespace Chips {
	Keypad::Keypad() {
		std::fill(_key, _key + KEYPAD_SIZE, 0); //reset keypad
	}
	
	BYTE Keypad::GetKey(BYTE index) {
		return _key[index];
	}
	
	void Keypad::SetKey(BYTE index, BYTE value) {
	 _key[index] = value;
	}
}
