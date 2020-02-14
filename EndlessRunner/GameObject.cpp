#include "GameObject.h"
#include "SDL.h"
#include "Game.h"
#include "Screen.h"

void GameObject::Update(float deltaTime)
{
}

void GameObject::Render(Screen* screen)
{
	auto renderer = screen->Renderer();

	SDL_Rect destination;
	destination.w = (int)(size.x_);
	destination.h = (int)(size.y_);
	destination.x = (int)(position.x_ - destination.w / 2 - screen->cameraPosition.x_) + screen->ShakeX();
	destination.y = (int)(position.y_ - destination.h / 2 - screen->cameraPosition.y_) + screen->ShakeY();

	SDL_RenderCopy(renderer, sprite->texture, NULL, &destination);
}
