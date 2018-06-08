#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace Chips {
	class MainWindow {
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
	public:
		MainWindow();
		
		void Close();
	};
}
#endif