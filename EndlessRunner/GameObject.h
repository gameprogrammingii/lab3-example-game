#pragma once

#include "HeliumMath.h"

using namespace Helium;

class Game;
struct Sprite;

class GameObject
{
public:
	Game* game;
	Sprite* sprite;
	Vector2 position;
	Vector2 size;
	virtual void Update(float deltaTime);
	virtual void Render();
};

