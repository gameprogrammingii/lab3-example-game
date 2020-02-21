#pragma once

#include "HeliumMath.h"
#include "GuiFont.h"

using namespace Helium;

class Game;
struct Sprite;
class Screen;

class GameObject
{
public:
	Game* game;
	Sprite* sprite;
	GuiFont* guiText;
	Vector2 position;
	Vector2 size;
	virtual void Update(float deltaTime);
	virtual void Render(Screen* screen);
	GameObject()
	{
		game = 0;
		sprite = 0;
		guiText = 0;
	}
	~GameObject()
	{
		if (guiText != 0)
			delete guiText;
		guiText = 0;
	}
};

