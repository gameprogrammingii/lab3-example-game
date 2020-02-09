#include "Ball.h"


void Ball::Update(float deltaTime)
{
	velocity = velocity + Gravity * deltaTime;
	position = position + velocity * deltaTime;

	if (position.x_ > maxX)
	{
		position.x_ = maxX;
		if (velocity.x_ > 0.0f) {
			velocity.x_ = -velocity.x_ * 0.9f;
		}
	}

	if (position.x_ < minX)
	{
		position.x_ = minX;
		if (velocity.x_ < 0.0f) {
			velocity.x_ = -velocity.x_ * 0.9f;
		}
	}
}

void Ball::Radius(float f) {
	size = Vector2(f * 2.0f, f * 2.0f);
}
