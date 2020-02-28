#include "Game.h"
#include "SDL.h"
#include "Screen.h"
#include <iostream>
#include <filesystem>
#include <algorithm>

Game::Game() : screen(this)
{

}

Game::~Game()
{
	printf("Destroy Game\n");

	for (auto sprite : sprites)
		delete sprite;

	sprites.clear();

	SDL_DestroyRenderer(renderer);
}

void Game::Init()
{
	screen.Init();
	renderer = SDL_CreateRenderer(screen.Window(), -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	vector<string> paths;
	for (const auto& entry :
		std::filesystem::directory_iterator("assets/background"))
	{
		if (entry.path().extension().string() == ".png")
		{
			paths.push_back(entry.path().string());
			//sprites.push_back(new Sprite());
		}
	}

	sort(paths.begin(), paths.end());

	for (const auto& path : paths)
	{
		sprites.push_back(new Sprite(path, renderer));
	}

	
}

void Game::Render(const GameObject& gameObject)
{
	auto time = ((float)SDL_GetTicks()) * 0.001f;
	auto scroll = (int)(time * (float)gameObject.layer);

	scroll %= screen.W;

	SDL_Rect destination{
		-scroll,
		0,screen.W, screen.H
	};

	SDL_RenderCopy(renderer, gameObject.sprite->texture, 0, &destination);
	destination.x += destination.w;
	SDL_RenderCopy(renderer, gameObject.sprite->texture, 0, &destination);
}

void Game::Run()
{
	Init();
	
	vector<GameObject> gameObjects;

	for (int i = 0; i < (int)sprites.size(); i++)
	{
		auto sprite = sprites[sprites.size() - 1 - i];

		GameObject gameObject{
			sprite, i * i * 3
		};

		gameObjects.push_back(gameObject);
	}
	
	/*GameObject gameObject{
		&sprite,
		100
	};*/

	const int framesPerSecond = 60;
	const int frameLength = 1000 / framesPerSecond;

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		auto time = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xdf, 0xef, 0xff, 0xff);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

		for (const auto& gameObject : gameObjects)
			Render(gameObject);

		SDL_RenderPresent(renderer);

		int timeElapsed = SDL_GetTicks() - time;
		int timeToWait = frameLength - timeElapsed;

		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}
	}
}

