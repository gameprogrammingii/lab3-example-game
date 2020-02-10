#pragma once

#include "SDL.h"
#include <map>
#include <string>
#include <SDL_mixer.h>
#include <iostream>

class Game;
using namespace std;

struct Sprite
{
	SDL_Texture* texture;
	~Sprite();
};

class AssetManager
{
	Game* game;
	map<string, Sprite*> sprites;
public:
	AssetManager(Game* game);
	~AssetManager();
	void Init();

	Sprite* GetSprite(string name) const;
};

