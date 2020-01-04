#pragma once
#include <glm\common.hpp>
#include <glm\vec3.hpp>

class Ball
{
private:
	glm::vec3 worldPos;
	float gravity;
	glm::vec3 velocity;
	float radius;
public:
	Ball();
	Ball(float x, float y, float z, float r);
	glm::vec3 getWorldPos();
	float getRadius();
	void applyGravity();
};

