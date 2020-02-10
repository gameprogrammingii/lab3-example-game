#include "Game.h"
#include "SDL.h"
#include "Screen.h"
#include <iostream>
#include "GameObject.h"
#include "AssetManager.h"
#include "Ball.h"
#include "Utility.h"

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
}

void SpawnBall(Game* game, vector<Ball*>& balls, float width, float height, float minX, float maxX, float maxY)
{
	auto ball = game->CreateGameObject<Ball>();
	ball->position = Vector2(width * 0.5f - 10 + rand() % 20, height * 0.5f - 10 + rand() % 20);
	ball->minX = minX;
	ball->maxX = maxX;
	ball->maxY = maxY;
	ball->Radius(13.0f + (float)(rand() % 5));
	ball->Type(rand() % 3);
	ball->velocity = Vector2((float)(100 - rand() % 200), (float)(-rand() % 100));
	balls.push_back(ball);
}

void Game::Run()
{
	Init();

	auto renderer = screen.Renderer();

	const int framesPerSecond = 60;
	const int frameLength = 1000 / framesPerSecond;

	const float deltaTime = 1.0f / (float)framesPerSecond;

	/*---- Game Play ----*/

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
		wall->position = Vector2(width * 0.5f, maxY + wallHalfSize);
		wall->size = Vector2(maxX - minX, wallSize);
		wall->sprite = assetManager.GetSprite("black");
	}
	{
		auto wall = CreateGameObject<GameObject>();
		wall->position = Vector2(minX - wallHalfSize, maxY - wallHeight * 0.5f);
		wall->size = Vector2(wallSize, wallHeight);
		wall->sprite = assetManager.GetSprite("black");
	}
	{
		auto wall = CreateGameObject<GameObject>();
		wall->position = Vector2(maxX + wallHalfSize, maxY - wallHeight * 0.5f);
		wall->size = Vector2(wallSize, wallHeight);
		wall->sprite = assetManager.GetSprite("black");
	}

	for (int i = 0; i < 50; i++)
	{
		SpawnBall(this, balls, width, height, minX, maxX, maxY);
	}

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
			case SDL_KEYDOWN:
				break;
			case SDL_MOUSEBUTTONDOWN:
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				Vector2 mousePosition = Vector2((float)x, (float)y);

				bool hit = false;

				for (int i = 0; i < (int)balls.size(); i++)
				{
					auto sqrDistance = (balls[i]->position - mousePosition).length_squared();
					if (sqrDistance < balls[i]->Radius() * balls[i]->Radius())
					{
						auto ball = balls[i];

						DestroyGameObject(ball);
						balls.erase(balls.begin() + i);

						hit = true;
						break;
					}
				}

				if (!hit)
					SpawnBall(this, balls, width, height, minX, maxX, maxY);
			}
			break;
			default:
				break;
			}

		}


		for (int i = 0; i < (int)balls.size(); i++)
		{
			for (int j = i + 1; j < (int)balls.size(); j++)
			{
				auto a = balls[i];
				auto b = balls[j];

				auto diff = a->position - b->position;

				auto combineRadius = a->Radius() + b->Radius();

				if (diff.length_squared() < combineRadius * combineRadius)
				{
					auto dir = diff.unit();
					auto overlap = combineRadius - diff.length();
					a->Separate(dir, overlap);
					b->Separate(-dir, overlap);
				}
			}
		}

		for (auto gameObject : gameObjects)
		{
			gameObject->Update(deltaTime);
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

