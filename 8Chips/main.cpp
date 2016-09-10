#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include "chip8.h"

const std::string WINDOW_NAME = "8Chips";
const int CHIP8_SCREEN_WIDTH = 64;
const int CHIP8_SCREEN_HEIGHT = 32;
const int WINDOW_RATIO = 10;

//TODO: CHANGE THE POSITION FROM GLOBAL TO LOCAL
SDL_Window* window = nullptr;
SDL_Surface* windowSurface = nullptr;

Chip8 chip8;

bool loadROM(std::string filename) {
	std::cout << "Loading: " << filename << std::endl;

	// Open file
	std::ifstream infile;
	infile.open(filename, std::ios::binary);
	if (!infile) {
		std::cout << "Error opening file." << std::endl;
		return false;
	}

	// Check file size
	infile.seekg(0, std::ios::end);
	long length = infile.tellg();
	infile.seekg(0, std::ios::beg);
	std::cout << "Filesize: " << static_cast<int>(length) << " bytes" << std::endl;

	// Allocate memory to contain the whole file
	char * buffer = new char[length];
	if (buffer == NULL) {
		std::cout << "Memory allocation failed." << std::endl;
		return false;
	}

	// Copy the file into the buffer
	infile.read(buffer, length);
	if (!infile) {
		std::cout << "Reading error" << std::endl;
		return false;
	}

	// Copy buffer to Chip8 memory
	//TODO: Change to variables instead of constant hard to modify numbers
	if ((4096 - 512) > length) {
		for (int i = 0; i < length; ++i)
			//Change this
			//memory[i + 512] = buffer[i];
			chip8.setMemoryByte(i + 512, (unsigned char)buffer[i]);
	} else {
		std::cout << "Error: ROM too big for memory" << std::endl;
		return false;
	}

	// Close file, free buffer
	infile.close();
	delete buffer;

	//TODO: maybe put this to chip8.cpp
	std::cout << "ROM Loaded." << std::endl;
	return true;
}

bool initWindow() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error: " << SDL_GetError() << std::endl;
		success = false;
	} else {
		window = SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CHIP8_SCREEN_WIDTH * WINDOW_RATIO, CHIP8_SCREEN_HEIGHT * WINDOW_RATIO, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "Error: " << SDL_GetError() << std::endl;
			success = false;
		} else {
			windowSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}

void updateWindowSurface() {
	//Set the 2 colors
	Uint32 offColor = SDL_MapRGB(windowSurface->format, 0x00, 0x00, 0x00); //black
	Uint32 onColor = SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF); //white
	
	Uint8 *pixel;

	//Lock the surface first in order to draw pixels
	if (SDL_MUSTLOCK(windowSurface)) {
		SDL_LockSurface(windowSurface);
	}

	int x = -1;

	//for loop to assign the pixels
	for (int i = 0; i< windowSurface->w; i++) {
		int y = -1;

		if (i % WINDOW_RATIO == 0) { x++; }

		for (int j = 0; j < windowSurface->h; j++) {
			if (j % WINDOW_RATIO == 0) y++;

			//Set pixel
			pixel = (Uint8*)windowSurface->pixels;
			pixel += (j * windowSurface->pitch) + (i * sizeof(Uint32));
			if (chip8.gfx[y*64 + x] == 0) {
				*((Uint32*)pixel) = offColor;
			} else {
				*((Uint32*)pixel) = onColor;
			}
		}
	}

	//Unlock the surface
	if (SDL_MUSTLOCK(windowSurface)) {
		SDL_UnlockSurface(windowSurface);
	}
}

void showErrorCode(int e, int c) {
	switch (e) {
	case 1:
		std::cout << "Unknown opcode [0x0000]: " << std::hex << c << std::endl;
		break;
	case 2:
		std::cout << "Unknown opcode [0x8000]: " << std::hex << c << std::endl;
		break;
	case 3:
		std::cout << "Unknown opcode [0xE000]: " << std::hex << c << std::endl;
		break;
	case 4:
		std::cout << "Unknown opcode [0xF000]: " << std::hex << c << std::endl;
		break;
	case 5:
		std::cout << "Unknown opcode: " << std::hex << c << std::endl;
		break;
	}
}

int main(int argc, char ** argv)
{
	std::string filename;

	//Get user input
	std::cout << "Welcome to 8Chips, a Chip8 emulator." << std::endl;
	std::cout << "Type the ROM file path below:" << std::endl;
	std::getline(std::cin, filename);
	
	//Load ROM file
	if (!loadROM(filename)) {
		return 1;
	}

	//Initialize Window
	if (!initWindow()) {
		return 1;
	}

	//Start SDL_Window sequence
	int errorCode = 0;
	bool isRunning = true;
	SDL_Event ev;
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	float frame_time = 0;
	float delta_time = 0;
	int prev_time = 0;
	int cur_time = 0;

	while (isRunning) {
		prev_time = cur_time;
		cur_time = SDL_GetTicks();
		delta_time = (cur_time - prev_time) / 1000.0f;
		frame_time += delta_time;

		//Input Handling
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				isRunning = false;
				break;
			}

			//Keyboard input
			chip8.key[0x0] = keys[SDL_SCANCODE_X];
			chip8.key[0x1] = keys[SDL_SCANCODE_1];
			chip8.key[0x2] = keys[SDL_SCANCODE_2];
			chip8.key[0x3] = keys[SDL_SCANCODE_3];
			chip8.key[0x4] = keys[SDL_SCANCODE_Q];
			chip8.key[0x5] = keys[SDL_SCANCODE_W];
			chip8.key[0x6] = keys[SDL_SCANCODE_E];
			chip8.key[0x7] = keys[SDL_SCANCODE_A];
			chip8.key[0x8] = keys[SDL_SCANCODE_S];
			chip8.key[0x9] = keys[SDL_SCANCODE_D];
			chip8.key[0xA] = keys[SDL_SCANCODE_Z];
			chip8.key[0xB] = keys[SDL_SCANCODE_C];
			chip8.key[0xC] = keys[SDL_SCANCODE_4];
			chip8.key[0xD] = keys[SDL_SCANCODE_R];
			chip8.key[0xE] = keys[SDL_SCANCODE_F];
			chip8.key[0xF] = keys[SDL_SCANCODE_V];
		}

		//Implement better framerate cap
		if (frame_time >= 1/60) {
			frame_time = 0;

			//Do cpu cycle and show errors if there are
			chip8.emulateCycle();
			if (chip8.errorCode != 0)
				showErrorCode(chip8.errorCode, chip8.getOpcode());

			if (chip8.getDrawFlag()) {
				updateWindowSurface();
				chip8.setDrawFlag(false);

				SDL_UpdateWindowSurface(window);
			}
		}
	}

	//Close Window, free memory
	SDL_DestroyWindow(window);
	windowSurface = nullptr;
	window = nullptr;
	SDL_Quit();

	return 0;
}
