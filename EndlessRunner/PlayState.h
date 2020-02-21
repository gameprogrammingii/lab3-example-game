#pragma once
#include "Game.h"
#include "SDL_mixer.h"

class PlayState :
	public State
{
	AssetManager* assetManager;
	void SpawnBall(float width, float height, float minX, float maxX, float maxY);

	vector<Ball*> balls;

	Mix_Chunk* spawnnew;

	int score = 0;
	int guiScore = 0;
	int guiScoreStartScore = 0;
	int guiScoreStartTime = 0;
	GameObject* scoreGameObject;

	void AddPointsToScore(int pointsToAdd)
	{
		score += pointsToAdd;
		guiScoreStartScore = guiScore;
		guiScoreStartTime = SDL_GetTicks();
	}

public:
	PlayState(Game* game);

	// Inherited via State
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Input(const SDL_Event& event) override;
};

