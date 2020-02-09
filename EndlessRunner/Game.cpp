#include "Game.h"
#include "SDL.h"
#include "Screen.h"
#include <iostream>

Game::Game() : screen(this)
{

}

Game::~Game()
{
	printf("Destroy Game\n");
}

void Game::Init()
{
	screen.Init();
}

void Game::Run()
{
	Init();

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
}

