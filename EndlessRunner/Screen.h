#pragma once

#include "SDL.h"

class Game;

class Screen
{
	Game* game;
	SDL_Window* window;
public:
	void Init();
	Screen(Game* game);
	~Screen();
	SDL_Window* Window() const { return window; }
	const int W = 800;
	const int H = 600;
};

