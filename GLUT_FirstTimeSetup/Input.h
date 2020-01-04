#pragma once
class Input
{
private:
	static int mouseX;
	static int mouseY;
	static bool wKeyDown;
	static bool sKeyDown;
	static bool dKeyDown;
	static bool aKeyDown;
	static int forward;
	static int right;
public:
	static int getMouseX();
	static int getMouseY();
	static void setMouseX(int x);
	static void setMouseY(int y);
	static void calcMovementAxes();
	static void setWKeyDown(bool down);
	static void setSKeyDown(bool down);
	static void setDKeyDown(bool down);
	static void setAKeyDown(bool down);
	static int getForward();
	static int getRight();
};

