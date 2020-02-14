#pragma once

#include "SDL.h"
#include "HeliumMath.h"
#include <cfloat>
#include "Easing.h"

class Game;

class Screen
{
	Game* game;
	SDL_Window* window;
	SDL_Renderer* renderer;

	const float shakeDuration = 2.0f;
	const float shakeAmount = 10.0f;
	const float shakeSpeed = 100.0f;

	float shakeStart = -FLT_MAX;
	float shakeEnd() { return shakeStart + shakeDuration; }

	static float GetTime() { return ((float)SDL_GetTicks()) * 0.001f; }

public:
	Helium::Vector2 cameraPosition;
	void Init();
	Screen(Game* game);
	~Screen();
	SDL_Renderer* Renderer() { return renderer; }
	void Render();



	void Shake()
	{
		shakeStart = GetTime();
	}

	int ShakeX()
	{
		float max = cos(GetTime() * shakeSpeed) * shakeAmount;
		float min = 0.0f;
		float startTime = shakeStart;
		float endTime = shakeEnd();
		float current = GetTime();

		/*
		@t is the current time (or position) of the tween. This can be seconds or frames, steps, seconds, ms, whatever – as long as the unit is the same as is used for the total time [3].
		@b is the beginning value of the property.
		@c is the change between the beginning and destination value of the property.
		@d is the total time of the tween.
		*/

		float t = current - startTime;
		float b = max;
		float c = -max;
		float d = endTime - startTime;

		if (t > d)return 0;


		float returnValue = Cubic_EaseOut(t, b, c, d);

		return (int)returnValue;
	}

	int ShakeY()
	{
		return 0;
	}
};

