#include "Game.h"
#include "SDL.h"
#include "Screen.h"
#include <iostream>
#include "GameObject.h"
#include "AssetManager.h"
#include "Ball.h"
#include "Utility.h"
#include "PlayState.h"

Game::Game() : screen(this), assetManager(this)
{
	state = NULL;
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

void Game::RenderGameObjects(Screen* screen)
{
	for (auto gameObject : gameObjects)
	{
		gameObject->Render(screen);
	}
}

void Game::DestroyGameObject(GameObject* gameObject)
{
	remove(gameObjects, gameObject);
	delete gameObject;
}

void Game::Init()
{
	screen.Init();
	assetManager.Init();
	SwitchToState<PlayState>();
}



void Game::Run()
{
	Init();

	auto renderer = screen.Renderer();

	const int framesPerSecond = 60;
	const int frameLength = 1000 / framesPerSecond;

	const float deltaTime = 1.0f / (float)framesPerSecond;

	const int updateIterations = 10;

	const float deltaTimeUpdate = deltaTime / (float)updateIterations;

	/*---- Game Play ----*/

	

	/*--------*/


	SDL_Event event;
	while (true)
	{
		auto time = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				return;
			default:
				state->Input(event);
				break;
			}

		}

		for (int u = 0; u < updateIterations; u++)
		{
			state->Update(deltaTimeUpdate);


			for (auto gameObject : gameObjects)
			{
				gameObject->Update(deltaTimeUpdate);
			}

		}

		screen.Render();

		int timeElapsed = SDL_GetTicks() - time;
		int timeToWait = frameLength - timeElapsed;

		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}
	}
}

