#include "Game.h"
#include "SDL.h"
#include "Screen.h"
#include <iostream>
#include "GameObject.h"
#include "AssetManager.h"
#include "Ball.h"

Game::Game() : screen(this), assetManager(this)
{
}

Game::~Game()
{
	printf("Destroy Game\n");
	ClearGameObjects();
}

void Game::ClearGameObjects()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
	gameObjects.clear();
}

void Game::Init()
{
	screen.Init();
	assetManager.Init();
}

void Game::Run()
{
	Init();

	auto renderer = screen.Renderer();

	const float width = 840.0f;
	const float height = 600.0f;
	const float maxY = height - 100.0f;
	const float minX = width * 0.5f - 200;
	const float maxX = width * 0.5f + 200;
	const float wallSize = 4.0f;
	const float wallHalfSize = wallSize * 0.5f;
	const float wallHeight = maxX - minX;

	{
		auto wall = CreateGameObject<GameObject>();
		wall->position = Vector2(width * 0.5f, maxY);
		wall->size = Vector2(maxX-minX, wallSize);
		wall->sprite = assetManager.GetSprite("black");
	}
	{
		auto wall = CreateGameObject<GameObject>();
		wall->position = Vector2(minX, maxY - wallHeight * 0.5f);
		wall->size = Vector2(wallSize, wallHeight);
		wall->sprite = assetManager.GetSprite("black");
	}
	{
		auto wall = CreateGameObject<GameObject>();
		wall->position = Vector2(maxX, maxY - wallHeight * 0.5f);
		wall->size = Vector2(wallSize, wallHeight);
		wall->sprite = assetManager.GetSprite("black");
	}

	{
		auto ball = CreateGameObject<Ball>();
		ball->position = Vector2(width * 0.5f, height * 0.5f);
		ball->minX = minX;
		ball->maxX = maxX;
		ball->maxY = maxY;
		ball->Radius(15.0f);
		ball->sprite = assetManager.GetSprite("red-circle");
		ball->velocity = Vector2(100, -100);
	}

	const int framesPerSecond = 60;
	const int frameLength = 1000 / framesPerSecond;

	SDL_Event event;
	while (true)
	{
		auto time = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return;
			}
		}

		for (auto gameObject : gameObjects)
		{
			gameObject->Update(0.001f * (float)frameLength);
		}

		SDL_SetRenderDrawColor(renderer, 0xef, 0xcf, 0xdf, 0xff);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

		for (auto gameObject : gameObjects)
		{
			gameObject->Render();
		}

		SDL_RenderPresent(renderer);

		int timeElapsed = SDL_GetTicks() - time;
		int timeToWait = frameLength - timeElapsed;

		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}
	}
}

