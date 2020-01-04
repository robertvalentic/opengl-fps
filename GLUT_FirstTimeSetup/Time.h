#pragma once
class Time
{
private:
	static float deltaTime;
public:
	static void setDeltaTime(float newDelta);
	static float getDeltaTime();
};

