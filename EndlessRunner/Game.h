#pragma once

#include "Screen.h"
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include <vector>

using namespace std;

struct Sprite
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	Sprite(string filename, SDL_Renderer* renderer)
	{
		surface = IMG_Load(filename.c_str());
		texture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	~Sprite() {
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
};

struct GameObject
{
	Sprite* sprite;
	int layer;
};

class Game
{
	SDL_Renderer* renderer;
	Screen screen;
	vector<Sprite*> sprites;

	void Init();
	void Render(const GameObject& gameObject);
public:
	void Run();
	Game();
	~Game();
};

