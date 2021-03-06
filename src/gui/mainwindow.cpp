#include "mainwindow.h"

namespace Chips {
	MainWindow::MainWindow() {
		//Create new window
		
		
		if(SDL_Init(SDL_INIT_VIDEO) != 0) {
			//Chips::Log().Get(Chips::logERROR) <<  "SDL couldn't initialize:" << SDL_GetError();
		//	return 1;
		}
		
		TTF_Init();
		TTF_Font* font = TTF_OpenFont("ARIAL.TTF", 12);
		SDL_Color foregroundColor = {255, 255, 255};
		SDL_Color backgroundColor = {0, 0, 255};
		SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "Hello World!", foregroundColor, backgroundColor);
		SDL_Rect textLocation = { 100, 100, 0, 0 }; 
		
		//Init screen dimensions
		SDL_Rect _screenRect = {0, 0, 320, 240};
		
		//Get device display mode
		SDL_DisplayMode displayMode;
		if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
			_screenRect.w = displayMode.w;
			_screenRect.h = displayMode.h;
		}
		
		//Create window
		window = SDL_CreateWindow("8Chips",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_screenRect.w,
			_screenRect.h,
			SDL_WINDOW_SHOWN);
			
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		SDL_BlitSurface(textSurface, NULL, renderer,  &textLocation);
		SDL_RenderPresent(renderer);
		
		SDL_Delay(2000);
		
		SDL_FreeSurface(textSurface);
		TTF_CloseFont(font);
		TTF_Quit();
	}
	
	void MainWindow::Close() {
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}