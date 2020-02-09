#include "PlayState.h"
#include "HeliumMath.h"
#include "GameObject.h"
#include "AssetManager.h"
#include "Ball.h"
using namespace Helium;

PlayState::PlayState(Game* game) : State(game)
{
	screen = game->GetScreen();
	renderer = screen->Renderer();
	assetManager = game->GetAssetManager();
}

void PlayState::Init()
{
	const float width = 840.0f;
	const float height = 600.0f;
	const float maxY = height - 100.0f;
	const float minX = width * 0.5f - 200;
	const float maxX = width * 0.5f + 200;
	const float wallSize = 4.0f;
	const float wallHalfSize = wallSize * 0.5f;
	const float wallHeight = maxX - minX;

	{
		auto wall = game->CreateGameObject<GameObject>();
		wall->position = Vector2(width * 0.5f, maxY + wallHalfSize);
		wall->size = Vector2(maxX - minX, wallSize);
		wall->sprite = assetManager->GetSprite("black");
	}
	{
		auto wall = game->CreateGameObject<GameObject>();
		wall->position = Vector2(minX - wallHalfSize, maxY - wallHeight * 0.5f);
		wall->size = Vector2(wallSize, wallHeight);
		wall->sprite = assetManager->GetSprite("black");
	}
	{
		auto wall = game->CreateGameObject<GameObject>();
		wall->position = Vector2(maxX + wallHalfSize, maxY - wallHeight * 0.5f);
		wall->size = Vector2(wallSize, wallHeight);
		wall->sprite = assetManager->GetSprite("black");
	}



	for (int i = 0; i < 50; i++)
	{
		auto ball = game->CreateGameObject<Ball>();
		ball->position = Vector2(width * 0.5f - 10 + rand() % 20, height * 0.5f - 10 + rand() % 20);
		ball->minX = minX;
		ball->maxX = maxX;
		ball->maxY = maxY;
		ball->Radius(13.0f + (float)(rand() % 5));
		ball->Type(rand() % 3);
		ball->velocity = Vector2(100 - rand() % 200, -rand() % 100);
		balls.push_back(ball);
	}
}

void PlayState::Update(float deltaTime)
{
	for (int i = 0; i < balls.size(); i++)
	{
		for (int j = i + 1; j < balls.size(); j++)
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
}
