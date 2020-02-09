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
};

