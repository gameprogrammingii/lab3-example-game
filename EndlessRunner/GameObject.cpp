#include "GameObject.h"
#include "SDL.h"
#include "Game.h"
#include "Screen.h"

void GameObject::Update(float deltaTime)
{
}

void GameObject::Render()
{
	auto screen = game->GetScreen();
	auto renderer = screen->Renderer();

	SDL_Rect destination;
	destination.w = (int)(size.x_);
	destination.h = (int)(size.y_);
	destination.x = (int)(position.x_ - destination.w / 2 - screen->cameraPosition.x_);
	destination.y = (int)(position.y_ - destination.h / 2 - screen->cameraPosition.y_);

	SDL_RenderCopy(renderer, sprite->texture, NULL, &destination);
}
