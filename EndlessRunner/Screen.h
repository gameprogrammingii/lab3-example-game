#pragma once

#include "SDL.h"
#include "HeliumMath.h"

class Game;

class Screen
{
	Game* game;
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	Helium::Vector2 cameraPosition;
	void Init();
	Screen(Game* game);
	~Screen();
	SDL_Renderer* Renderer() { return renderer; }
};

