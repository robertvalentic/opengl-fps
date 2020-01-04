#include "Input.h"

int Input::mouseX;
int Input::mouseY;
bool Input::wKeyDown;
bool Input::sKeyDown;
bool Input::dKeyDown;
bool Input::aKeyDown;
int Input::forward;
int Input::right;

int Input::getMouseX()
{
	return mouseX;
}

int Input::getMouseY()
{
	return mouseY;
}

void Input::setMouseX(int x)
{
	mouseX = x;
}

void Input::setMouseY(int y)
{
	mouseY = y;
}

void Input::calcMovementAxes()
{
	if (wKeyDown)
	{
		forward = 1;
	}
	if (sKeyDown)
	{
		forward = -1;
	}
	if (!wKeyDown && !sKeyDown)
	{
		forward = 0;
	}
	if (dKeyDown)
	{
		right = 1;
	}
	if (aKeyDown)
	{
		right = -1;
	}
	if (!dKeyDown && !aKeyDown)
	{
		right = 0;
	}
}

void Input::setWKeyDown(bool down)
{
	wKeyDown = down;
}

void Input::setSKeyDown(bool down)
{
	sKeyDown = down;
}

void Input::setDKeyDown(bool down)
{
	dKeyDown = down;
}

void Input::setAKeyDown(bool down)
{
	aKeyDown = down;
}

int Input::getForward()
{
	return forward;
}

int Input::getRight()
{
	return right;
}