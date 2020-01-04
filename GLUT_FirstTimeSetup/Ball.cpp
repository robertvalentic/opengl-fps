#include "Ball.h"
#include "Time.h"
#include <iostream>

Ball::Ball(float x, float y, float z, float r)
{
	worldPos.x = x;
	worldPos.y = y;
	worldPos.z = z;
	radius = r;
	velocity = glm::vec3(0,0,0);
	gravity = 19.807f;
}

glm::vec3 Ball::getWorldPos()
{
	return worldPos;
}

float Ball::getRadius()
{
	return radius;
}

void Ball::applyGravity()
{
	velocity.y -= Time::getDeltaTime() * gravity;

	worldPos += Time::getDeltaTime() * velocity;
	
	if (worldPos.y - radius <= 0)
	{
		worldPos.y = radius;
	}
}
