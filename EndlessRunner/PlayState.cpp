#include "PlayState.h"
#include "HeliumMath.h"
#include "GameObject.h"
#include "Ball.h"

using namespace Helium;

void PlayState::SpawnBall(float width, float height, float minX, float maxX, float maxY)
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

PlayState::PlayState(Game* game) : State(game)
{
	this->assetManager = game->GetAssetManager();
}

void PlayState::Init()
{
	spawnnew = assetManager->GetSound("spawnnew")->data;

	game->ClearGameObjects();

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
		SpawnBall(width, height, minX, maxX, maxY);
	}

	Mix_PlayMusic(assetManager->GetMusic("bgmusic")->data, -1);
}

void PlayState::Update(float deltaTime)
{
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
}

void PlayState::Input(const SDL_Event& event)
{
	const float width = 840.0f;
	const float height = 600.0f;
	const float maxY = height - 100.0f;
	const float minX = width * 0.5f - 200;
	const float maxX = width * 0.5f + 200;
	const float wallSize = 4.0f;
	const float wallHalfSize = wallSize * 0.5f;
	const float wallHeight = maxX - minX;

	switch (event.type)
	{
	case SDL_QUIT:
		return;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
		{
			game->SwitchToState<PlayState>();
		}
			break;
		default:
			break;
		}
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

				bool bad = ball->Type() == 0;

				string soundName = bad ? "bad" : "good";

				Mix_PlayChannel(-1, assetManager->GetSound(soundName)->data, 0);

				game->DestroyGameObject(ball);
				balls.erase(balls.begin() + i);

				hit = true;
				break;
			}
		}

		if (!hit)
		{
			Mix_PlayChannel(-1, spawnnew, 0);
			SpawnBall(width, height, minX, maxX, maxY);
		}
	}
	break;
	default:
		break;
	}
}
