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

struct Music
{
	Mix_Music* data;
	Music(string filename)
	{
		data = Mix_LoadMUS(filename.c_str());
		if (data == NULL)
		{
			//cout << Mix_GetError() << endl;
			throw runtime_error(Mix_GetError());
		}
	}
	~Music()
	{
		Mix_FreeMusic(data);
		data = NULL;
	}
};

struct Sound
{
	Mix_Chunk* data;
	Sound(string filename)
	{
		data = Mix_LoadWAV(filename.c_str());
		if (data == NULL)
		{
			//cout << Mix_GetError() << endl;
			throw runtime_error(Mix_GetError());
		}
	}
	~Sound()
	{
		Mix_FreeChunk(data);
		data = NULL;
	}
};


class AssetManager
{
	Game* game;
	map<string, Sprite*> sprites;
	map<string, Music*> musics;
	map<string, Sound*> sounds;
public:
	AssetManager(Game* game);
	~AssetManager();
	void Init();

	Sprite* GetSprite(string name) const;
	Music* GetMusic(string name) const;
	Sound* GetSound(string name) const;
};

