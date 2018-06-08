#include "chip8.h"

#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h> //TODO: CHANGE THIS IF NEEDED
//#include <windows.h>

#include "log.h"

namespace Chips {
	Chip8::Chip8() :
		_cpu(),
		_memory(),
		_keypad(),
		_opcodes(_cpu, _memory, _keypad)
		{
	isRunning = true;
	_curOpcode = 0; //clear opcode

	srand((unsigned int)time(NULL)); //Randomize

	int errorCode = 0;
	
	//Log().Get() << "Core initialized";
}

Chip8::~Chip8() {
	//Log().Get() << "Core closed";
}

bool Chip8::LoadRom(const std::string& fileName) {
	//Log().Get() << "Loading: " << fileName;
	
	bool result;
	// Open file
	std::ifstream infile;
	infile.open(fileName, std::ios::binary);
	if (!infile) {
		//Log().Get(logERROR) << "Failed opening file";
		result = false;
	} else {
		// Check file size
		infile.seekg(0, std::ios::end);
		long length = infile.tellg();
		infile.seekg(0, std::ios::beg);
	
		//Log().Get() << "File size: " << static_cast<int>(length) << " bytes";

		// Allocate memory to contain the whole file
		char * buffer = new char[length];
		if (buffer == NULL) {
			//Log().Get(logERROR) << "Memory allocation failed";
			result = false;
		} else {
			// Copy the file into the buffer
			infile.read(buffer, length);
			if (!infile) {
				//Log().Get(logERROR) << "Reading file failed";
				result = false;
			} else {	
				// Copy buffer to Chip8 memory
				if ((MEMORY_SIZE - MEMORY_DATA_START) > length) {
					for (int i = 0; i < length; i++)
						_memory.SetMemory(i + MEMORY_DATA_START, buffer[i]);
				} else {
					//Log().Get(logERROR) << "ROM too big for memory";
					result = false;
				}
			}
		}
		
		// Close file, free buffer
		infile.close();
		delete buffer;

		//Log().Get() << "ROM Loaded";
		result = true;
	}
	
	return result;	
}

void Chip8::Step() {

	//Fetch opcode
	_curOpcode = (_memory.GetMemory(_cpu.GetPC()) << 8) | (_memory.GetMemory(_cpu.GetPC() + 1));
	
	//Log().Get(logDEBUG) << "Opcode: " << _curOpcode;
	//Execute opcode
	_opcodes.Execute(_curOpcode);

	// Update timers
	//Change update from per cycle to per frame
	if (_cpu.GetDelayTimer() > 0)
		_cpu.DecDelayTimer();

	if (_cpu.GetSoundTimer() > 0) {
		if (_cpu.GetSoundTimer() == 1)
			//Beep(440, 200);
		_cpu.DecSoundTimer();
	}
}

bool Chip8::IsRunning() {
	return isRunning;
}
	
WORD Chip8::GetOpcode() {
	return _curOpcode;
}

void Chip8::SetOpcode(WORD value) {
	_curOpcode = value;
}
}