// GLUT_FirstTimeSetup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__ 
	#include <GLUT/glut.h>
#else
	#include <GL\freeglut.h>
#endif

#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Ball.h"

const GLfloat light_position[] = { 0.5f, 0.5f, 1.0f, 0.0f };
const int numOfArtifacts = 500;

int windowWidth{ 800 }, windowHeight{ 600 };
int oldMouseX{}, oldMouseY{}; // mouse position last frame
glm::vec3 positions[numOfArtifacts];

void changeSize(int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	// prevent divide by 0, when window is too short
	if (h == 0)
	{
		h = 1;
	}
	float ratio = 1.0 * w / h;

	// use the projection matrix
	glMatrixMode(GL_PROJECTION);

	// reset matrix
	glLoadIdentity();

	// set viewport to be the entire window
	glViewport(0, 0, w, h);

	// set the correct perspective
	gluPerspective(90, ratio, 0.1f, 1000.0f);

	// get back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawArtifact(float x, float y, float z, float angle)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, 0, 1, 0);
	//glScalef(1, 3, 1);

	/*glColor3f(x / 100, y / 100, z / 100);
	glutSolidTeapot(1.0f);*/
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f, 0.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0);
		glVertex3f(0.0f, 2.0f, 0.0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
		glVertex3f(0, 0.0f, 2.0f);
		glVertex3f(0, 0.0f, -2.0);
		glVertex3f(0.0f, 2.0f, 0.0);
	glEnd();
	glPopMatrix();
}

void drawSnowMan(float x, float y, float z, float angle) 
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, 0, 1, 0);

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 12, 12);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 12, 12);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 5, 5);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 5, 5);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);

	glPopMatrix();
}

float angle = 0.0f;
float red{1.0f}, blue{1.0f}, green{1.0f};
Player player = Player(0.0f, 1.5f, 10.0f);
int oldTimeSinceStart{};
Ball ball = Ball(0, 1000, -5, 1);

void renderScene(void)
{
	// Calculate delta time / frame time
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	Time::setDeltaTime((timeSinceStart - oldTimeSinceStart)/1000.0f); // Convert from milliseconds to seconds
	oldTimeSinceStart = timeSinceStart;

	//std::cout << Time::getDeltaTime() << std::endl;

	// enable wireframe view
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// clear colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	// reset transformations
	glLoadIdentity();

	player.updatePosRot();
	/*printf("x=%f, y=%f, z=%f, w=%f\n", player.getWorldLookPoint().x, player.getWorldLookPoint().y, player.getWorldLookPoint().z, player.getWorldLookPoint().w);*/

	// FPS Spoon
	glColor3f(0, 1, .9);
	glTranslatef(0.15f, -0.25, -0.5);
	glutSolidTeaspoon(1);

	// set the camera
	gluLookAt(	player.getWorldPos().x, player.getWorldPos().y, player.getWorldPos().z,
				player.getWorldLookPoint().x, player.getWorldLookPoint().y, player.getWorldLookPoint().z,
				0.0f, 1.0f, 0.0f);

	// Draw our physics ball
	ball.applyGravity();
	glPushMatrix();
	glTranslatef(ball.getWorldPos().x, ball.getWorldPos().y, ball.getWorldPos().z);
	glColor3f(0, 1, 0);
	glutSolidSphere(ball.getRadius(), 20, 20);
	glPopMatrix();

	for (int i = 0; i < numOfArtifacts; i++)
	{
		if (i % 2 == 1)
		{
			drawSnowMan(positions[i].x, positions[i].y, positions[i].z, angle);
		}
		else
		{
			drawArtifact(positions[i].x, positions[i].y, positions[i].z, angle);
		}
	}

	// Floor
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_QUADS);
		glVertex3f(-100, 0, 100);
		glVertex3f(-100, 0, -100);
		glVertex3f(100, 0, -100);
		glVertex3f(100, 0, 100);
	glEnd();

	angle += 0.3f;

	glutSwapBuffers();
}

void mouseInput(int x, int y)
{
	Input::setMouseX(windowWidth / 2 - x);
	Input::setMouseY(windowHeight / 2 - y);
	if (x != windowWidth / 2 || y != windowHeight / 2)
	{
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) 
	{
		case GLUT_KEY_F1:
			red = 1.0;
			green = 0.0;
			blue = 0.0; 
			break;
		case GLUT_KEY_F2:
			red = 0.0;
			green = 1.0;
			blue = 0.0; 
			break;
		case GLUT_KEY_F3:
			red = 0.0;
			green = 0.0;
			blue = 1.0; 
			break;
	}
}

void keyPress(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
	}

	if (key == 'w')
	{
		Input::setWKeyDown(true);
	}
	if (key == 's')
	{
		Input::setSKeyDown(true);
	}
	if (key == 'd')
	{
		Input::setDKeyDown(true);
	}
	if (key == 'a')
	{
		Input::setAKeyDown(true);
	}

	Input::calcMovementAxes();
}

void keyRelease(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		Input::setWKeyDown(false);
	}
	if (key == 's')
	{
		Input::setSKeyDown(false);
	}
	if (key == 'd')
	{
		Input::setDKeyDown(false);
	}
	if (key == 'a')
	{
		Input::setAKeyDown(false);
	}

	Input::calcMovementAxes();
}

void init()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	
	// Depth info
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Generate spawn locations for artifacts
	for (int i = 0; i < numOfArtifacts; i++)
	{
		int rNums[3];

		for (int j = 0; j < 3; j++)
		{
			if (rand() % 2 == 1)
			{
				rNums[j] = rand() % 100;
			}
			else
			{
				rNums[j] = -1 * (rand() % 100);
			}
		}

		positions[i] = glm::vec3(rNums[0],0, rNums[2]);
	}
}

int main(int argc, char** argv) 
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");
	//glutFullScreen();
	
	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	// input callbacks
	glutPassiveMotionFunc(mouseInput);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyRelease);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

