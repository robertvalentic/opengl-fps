#include "Player.h"
#include "Input.h"
#include "Time.h"
#include <glm\gtx\transform.hpp>
#include <iostream>

Player::Player()
{
	worldPos = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	localLookDir = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	worldLookPoint = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	mouseSens = 10.0f;
	movementSpeed = 0.05f;
	colliderRadius = 1;
}

Player::Player(float x, float y, float z)
{
	worldPos = glm::vec4(x, y, z, 1.0f);
	localLookDir = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	worldLookPoint = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	mouseSens = 10.0f;
	movementSpeed = 0.05f;
	colliderRadius = 1;
}

glm::vec4 Player::getWorldPos()
{
	return worldPos;
}

glm::vec4 Player::getWorldLookPoint()
{
	return worldLookPoint;
}

void Player::rotateLookDir()
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians((float)Input::getMouseX()*Time::getDeltaTime()*mouseSens), glm::vec3(0,1,0));
	trans = glm::rotate(trans, glm::radians((float)Input::getMouseY()*Time::getDeltaTime()*mouseSens), rightVec);
	localLookDir = trans * localLookDir;
	//printf("x=%f, y=%f, z=%f, w=%f\n", localLookDir.x, localLookDir.y, localLookDir.z, localLookDir.w);
}

void Player::calcLookPoint()
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(worldPos.x, worldPos.y, worldPos.z));
	trans = glm::translate(trans, glm::vec3(localLookDir.x, localLookDir.y, localLookDir.z));
	glm::vec4 worldOrigin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	worldLookPoint = trans * worldOrigin;
}

void Player::translateWorldPos()
{
	worldPos.x += Input::getForward() * forwardVec.x * movementSpeed;
	//worldPos.y += Input::getForward() * localLookDir.y * movementSpeed;
	worldPos.z += Input::getForward() * forwardVec.z * movementSpeed;

	worldPos.x += Input::getRight() * rightVec.x * movementSpeed;
	//worldPos.y += Input::getRight() * rightVec.y * movementSpeed;
	worldPos.z += Input::getRight() * rightVec.z * movementSpeed;

}

void Player::updatePosRot()
{
	calcRightVec();
	calcForwardVec();
	translateWorldPos();
	rotateLookDir();
	calcLookPoint();
}

void Player::calcRightVec()
{
	rightVec = glm::normalize(glm::cross(glm::vec3(localLookDir.x, localLookDir.y, localLookDir.z), glm::vec3(0, 1, 0)));
}

void Player::calcForwardVec()
{
	forwardVec = glm::normalize(glm::cross(glm::vec3(0, 1, 0), rightVec));
}