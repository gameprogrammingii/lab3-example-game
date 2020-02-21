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

	if (sprite != 0)
	{
		SDL_Rect destination;
		destination.w = (int)(size.x_);
		destination.h = (int)(size.y_);
		destination.x = (int)(position.x_ - destination.w / 2 - screen->cameraPosition.x_) + screen->ShakeX();
		destination.y = (int)(position.y_ - destination.h / 2 - screen->cameraPosition.y_) + screen->ShakeY();

		SDL_RenderCopy(renderer, sprite->texture, NULL, &destination);
	}

	if (guiText != 0)
	{
		SDL_Surface* surface =
			TTF_RenderText_Solid(guiText->font->data,
				guiText->text.c_str(), 
				guiText->textColor);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(
			renderer,
			surface
		);

		SDL_Rect destination;
		destination.w = surface->w;
		destination.h = surface->h;
		destination.x = (int)(position.x_ - screen->cameraPosition.x_) + screen->ShakeX();
		destination.y = (int)(position.y_ - screen->cameraPosition.y_) + screen->ShakeY();

		SDL_RenderCopy(renderer, texture, NULL, &destination);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}
}
