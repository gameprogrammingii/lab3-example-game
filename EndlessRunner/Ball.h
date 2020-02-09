#pragma once
#include "GameObject.h"
#include "HeliumMath.h"

using namespace Helium;

#define Gravity Vector2(0.0f, 100.0f)
#define Bounce 0.99f
#define Drag 0.01f

class Ball :
	public GameObject
{
	int type;
public:
	Vector2 velocity;
	float minX, maxX, maxY;
	virtual void Update(float deltaTime) override;
	void Radius(float f);
	float Radius() const;

	int Type()const;
	void Type(int type);
	void Separate(const Vector2& direction, float overlap);
};

