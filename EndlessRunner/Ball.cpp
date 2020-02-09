#include "Ball.h"
#include "Game.h"
#include "AssetManager.h"

void Ball::Update(float deltaTime)
{
	Vector2 antiVelocity = -velocity;
	velocity = velocity + antiVelocity * Drag * deltaTime;

	velocity = velocity + Gravity * deltaTime;
	position = position + velocity * deltaTime;

	float maxX = this->maxX - Radius();
	float minX = this->minX + Radius();
	float maxY = this->maxY - Radius();

	if (position.x_ > maxX)
	{
		position.x_ = maxX;
		if (velocity.x_ > 0.0f) {
			velocity.x_ = -velocity.x_ * Bounce;
		}
	}

	if (position.x_ < minX)
	{
		position.x_ = minX;
		if (velocity.x_ < 0.0f) {
			velocity.x_ = -velocity.x_ * Bounce;
		}
	}

	if (position.y_ > maxY)
	{
		position.y_ = maxY;
		if (velocity.y_ > 0.0f) {
			velocity.y_ = -velocity.y_ * Bounce;
		}
	}
}

void Ball::Radius(float f) {
	size = Vector2(f * 2.0f, f * 2.0f);
}

float Ball::Radius() const
{
	return size.x_ * 0.5f;
}

int Ball::Type() const { return type; }

void Ball::Type(int type)
{
	this->type = type;

	std::string spriteId = type == 0 ? "red-circle" : type == 1 ? "green-circle" : "blue-circle";

	sprite = game->GetAssetManager()->GetSprite(spriteId);
}

void Ball::Separate(const Vector2& direction, float overlap)
{
	position = position + direction * overlap * 0.5f;

	auto anti = -direction;

	float dot = anti.dot(velocity);
	if (dot > 0.0f)
		velocity = velocity + direction * dot * 2.0f * Bounce;
}
