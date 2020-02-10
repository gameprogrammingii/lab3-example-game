#include "AssetManager.h"
#include "HeliumMath.h"
#include "Game.h"
#include "Screen.h"
#include <iostream>

using namespace Helium;

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
}

AssetManager::AssetManager(Game* game)
{
	this->game = game;
}

AssetManager::~AssetManager()
{
	printf("Destroy Assets\n");
	for (auto sprite : sprites)
	{
		std::cout << "Destroy: " << sprite.first << std::endl;
		delete sprite.second;
	}
	sprites.clear();
}

SDL_Surface* CreateCircle(int size, int r, int g, int b)
{
	auto surface = SDL_CreateRGBSurface(0, size, size, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

	float middle = ((float)(size - 1)) * 0.5f;
	auto center = Vector2(middle, middle);

	float radiusSqr = middle * middle;

	auto colorInside = SDL_MapRGBA(surface->format, r, g, b, 0xff);
	auto colorOutside = SDL_MapRGBA(surface->format, r, g, b, 0x00);

	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			auto pos = Vector2((float)x, (float)y);

			bool inside = (pos - center).length_squared() < radiusSqr;

			*((Uint32*)surface->pixels + (x * size + y)) = inside ? colorInside : colorOutside;
		}
	}

	return surface;
}

void AssetManager::Init()
{
	{
		auto surface = CreateCircle(100, 0xff, 0x00, 0x00);
		auto texture = SDL_CreateTextureFromSurface(game->GetScreen()->Renderer(), surface);
		SDL_FreeSurface(surface);
		sprites["red-circle"] = new Sprite{ texture };
	}
	{
		auto surface = CreateCircle(100, 0x00, 0xff, 0x00);
		auto texture = SDL_CreateTextureFromSurface(game->GetScreen()->Renderer(), surface);
		SDL_FreeSurface(surface);
		sprites["green-circle"] = new Sprite{ texture };
	}
	{
		auto surface = CreateCircle(100, 0x00, 0x00, 0xff);
		auto texture = SDL_CreateTextureFromSurface(game->GetScreen()->Renderer(), surface);
		SDL_FreeSurface(surface);
		sprites["blue-circle"] = new Sprite{ texture };
	}

	{
		auto surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

		auto color = SDL_MapRGBA(surface->format, 0x11, 0x22, 0x33, 0xff);

		*((Uint32*)surface->pixels) = color;

		auto texture = SDL_CreateTextureFromSurface(game->GetScreen()->Renderer(), surface);
		SDL_FreeSurface(surface);
		sprites["black"] = new Sprite{ texture };
	}
}

Sprite* AssetManager::GetSprite(string name) const
{
	return sprites.find(name)->second;
}