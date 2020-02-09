
#include <iostream>
#include "SDL.h"

int main(int argc, char* args[])
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to Init SDL_Init, %s", SDL_GetError());
		return -1;
	}

	// Create a window of size (800 x 600)
	SDL_Window* window = SDL_CreateWindow("Hello World",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		600,
		SDL_WINDOW_ALLOW_HIGHDPI);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	// Destroy window (do not use delete window)
	SDL_DestroyWindow(window);

	// Quit SDL
	SDL_Quit();
	return 0;
}
