#pragma once
#include <glm\common.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>

class Player
{
private:
	glm::vec4 worldPos;
	glm::vec4 localLookDir;
	glm::vec4 worldLookPoint;
	glm::vec3 rightVec;
	glm::vec3 forwardVec;
	void calcLookPoint();
	void calcRightVec();
	void calcForwardVec();
	float mouseSens;
	float movementSpeed;
	float colliderRadius;
public:
	Player();
	Player(float x, float y, float z);
	glm::vec4 getWorldPos();
	glm::vec4 getWorldLookPoint();
	void updatePosRot();
	void rotateLookDir();
	void translateWorldPos();
};

