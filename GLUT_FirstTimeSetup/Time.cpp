#include "Time.h"

float Time::deltaTime;

void Time::setDeltaTime(float newDelta)
{
	deltaTime = newDelta;
}

float Time::getDeltaTime()
{
	return deltaTime;
}
