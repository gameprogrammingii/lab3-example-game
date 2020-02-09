#include "Screen.h"
#include "Game.h"
#include <iostream>

void Screen::Init()
{
	window = SDL_CreateWindow("Endless Runner",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		600,
		SDL_WINDOW_ALLOW_HIGHDPI);

	renderer = SDL_CreateRenderer(window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Screen::Screen(Game* game)
{
	this->game = game;
	window = NULL;
	renderer = NULL;
}

Screen::~Screen()
{
	printf("Destroy Screen\n");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Screen::Render()
{
	SDL_SetRenderDrawColor(renderer, 0xef, 0xcf, 0xdf, 0xff);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	game->RenderGameObjects();

	SDL_RenderPresent(renderer);
}
