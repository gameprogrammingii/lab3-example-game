#pragma once
#include "GameObject.h"
#include "HeliumMath.h"

using namespace Helium;

#define Gravity Vector2(0.0f, 100.0f)

class Ball :
	public GameObject
{
public:
	Vector2 velocity;
	float minX, maxX, maxY;
	virtual void Update(float deltaTime) override;
	void Radius(float f);
};

