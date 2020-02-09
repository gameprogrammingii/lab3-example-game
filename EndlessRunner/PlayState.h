#pragma once
#include "Game.h"

class Ball;

class PlayState :
	public State
{
	Screen* screen;
	SDL_Renderer* renderer;
	AssetManager* assetManager;
	vector<Ball*> balls;
public:
	PlayState(Game* game);
	// Inherited via State
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
};

