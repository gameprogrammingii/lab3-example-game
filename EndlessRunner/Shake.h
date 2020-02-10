#pragma once

struct Shake
{
	float amount;
	float speed;

	void Shake()
	{
		currentTime = 0.0f;
	}

	float Update(float deltaTime)
	{

	}
private:
	float currentTime;
};