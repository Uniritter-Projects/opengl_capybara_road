#include <iostream>
#include "Render.h"
#include<time.h> 
using namespace std;

struct car {
	char direction;
	int xPos;
	int yPos;
	float velocity;
	int xSize = 15;
	int ySize = 15;
	bool spawn = false;
	float rgb[3] = { 0, 0, 0 };
};

struct capybara {
	int xPos;
	int yPos;
	int xSize = 2;
	int ySize = 5;
};

//Game mechanics
int stage = 1;
int cameraMode = 2;

//Capybara
capybara capybaraEntity;

//Cars
const int carsCount = 10;
float carMove;
float randCarVelocity;
car cars[carsCount];

void DrawCapybara3D(float r, float g, float b) {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(15.0f, 5.0f, -10.0f);
	glVertex3f(-5.0f, 5.0f, -10.0f);
	glVertex3f(-5.0f, 5.0f, 10.0f);
	glVertex3f(15.0f, 5.0f, 10.0f);

	glColor3f(r, g, b);
	glVertex3f(15.0f, -5.0f, 10.0f);
	glVertex3f(-5.0f, -5.0f, 10.0f);
	glVertex3f(-5.0f, -5.0f, -10.0f);
	glVertex3f(15.0f, -5.0f, -10.0f);

	glColor3f(r, g, b);
	glVertex3f(15.0f, 5.0f, 10.0f);
	glVertex3f(-5.0f, 5.0f, 10.0f);
	glVertex3f(-5.0f, -5.0f, 10.0f);
	glVertex3f(15.0f, -5.0f, 10.0f);

	glColor3f(r, g, b);
	glVertex3f(15.0f, -5.0f, -10.0f);
	glVertex3f(-5.0f, -5.0f, -10.0f);
	glVertex3f(-5.0f, 5.0f, -10.0f);
	glVertex3f(15.0f, 5.0f, -10.0f);

	glColor3f(r, g, b);
	glVertex3f(-5.0f, 5.0f, 10.0f);
	glVertex3f(-5.0f, 5.0f, -10.0f);
	glVertex3f(-5.0f, -5.0f, -10.0f);
	glVertex3f(-5.0f, -5.0f, 10.0f);

	glColor3f(r, g, b);
	glVertex3f(15.0f, 5.0f, -10.0f);
	glVertex3f(15.0f, 5.0f, 10.0f);
	glVertex3f(15.0f, -5.0f, 10.0f);
	glVertex3f(15.0f, -5.0f, -10.0f);
	glEnd();
}

void DrawCar3D(int i) {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	#pragma region CarBase

	glBegin(GL_QUADS);

	glColor4f(cars[i].rgb[0], cars[i].rgb[1], cars[i].rgb[2], 1.0f);

	glVertex3f(15.0f + cars[i].xPos, 5.0f, -5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, 5.0f, -5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, 5.0f, 5.0f + cars[i].yPos);
	glVertex3f(15.0f + cars[i].xPos, 5.0f, 5.0f + cars[i].yPos);

	glVertex3f(15.0f + cars[i].xPos, -5.0f, 5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, -5.0f, 5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, -5.0f, -5.0f + cars[i].yPos);
	glVertex3f(15.0f + cars[i].xPos, -5.0f, -5.0f + cars[i].yPos);

	glVertex3f(15.0f + cars[i].xPos, 5.0f, 5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, 5.0f, 5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, -5.0f, 5.0f + cars[i].yPos);
	glVertex3f(15.0f + cars[i].xPos, -5.0f, 5.0f + cars[i].yPos);

	glVertex3f(15.0f + cars[i].xPos, -5.0f, -5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, -5.0f, -5.0f + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, 5.0f, -5.0f + cars[i].yPos);
	glVertex3f(15.0f + cars[i].xPos, 5.0f, -5.0f + cars[i].yPos);

	glVertex3f(-5.0f + cars[i].xPos, 5.0f, 5 + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, 5.0f, -5 + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, -5.0f, -5 + cars[i].yPos);
	glVertex3f(-5.0f + cars[i].xPos, -5.0f, 5 + cars[i].yPos);

	glVertex3f(15.0f + cars[i].xPos, 5.0f, -5 + cars[i].yPos);
	glVertex3f(15.0f + cars[i].xPos, 5.0f, 5 + cars[i].yPos);
	glVertex3f(15.0f + cars[i].xPos, -5.0f, 5 + cars[i].yPos);
	glVertex3f(15.0f + cars[i].xPos, -5.0f, -5 + cars[i].yPos);

	glEnd();

	#pragma endregion

	#pragma region CarHood

	glBegin(GL_QUADS);

	glColor4f(1, 1, 1, 1.0f);

	glVertex3f(7.5 + 2 + cars[i].xPos, 2, -3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, 2, -3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, 2, 3 + cars[i].yPos);
	glVertex3f(7.5 + 2 + cars[i].xPos, 2, 3 + cars[i].yPos);

	glVertex3f(7.5 + 2 + cars[i].xPos, -2, 3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, -2, 3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, -2, -3 + cars[i].yPos);
	glVertex3f(7.5 + 2 + cars[i].xPos, -2, -3 + cars[i].yPos);

	glVertex3f(7.5 + 2 + cars[i].xPos, 2, 3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, 2, 3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, -2, 3 + cars[i].yPos);
	glVertex3f(7.5 + 2 + cars[i].xPos, -2, 3 + cars[i].yPos);

	glVertex3f(7.5 + 2 + cars[i].xPos, -2, -3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, -2, -3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, 2, -3 + cars[i].yPos);
	glVertex3f(7.5 + 2 + cars[i].xPos, 2, -3 + cars[i].yPos);

	glVertex3f(-2.5 + 2 + cars[i].xPos, 2, 3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, 2, -3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, -2, -3 + cars[i].yPos);
	glVertex3f(-2.5 + 2 + cars[i].xPos, -2, 3 + cars[i].yPos);

	glVertex3f(7.5 + 2 + cars[i].xPos, 2, -3 + cars[i].yPos);
	glVertex3f(7.5 + 2 + cars[i].xPos, 2, 3 + cars[i].yPos);
	glVertex3f(7.5 + 2 + cars[i].xPos, -2, 3 + cars[i].yPos);
	glVertex3f(7.5 + 2 + cars[i].xPos, -2, -3 + cars[i].yPos);

	glEnd();

	#pragma endregion
}

void DrawCube(float r, float g, float b) {
	//Comandos para habilitar a transparencia em areas sobrepostas
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Base
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3i(-10, -5, -10);
	glVertex3i(10, -5, -10);
	glVertex3i(10, -5, 10);
	glVertex3i(-10, -5, 10);
	glEnd();

	//Top
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3i(-10, -25, -10);
	glVertex3i(10, -25, -10);
	glVertex3i(10, -25, 10);
	glVertex3i(-10, -25, 10);
	glEnd();

	//Left
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3i(10, -5, -10);
	glVertex3i(-10, -5, -10);
	glVertex3i(-10, -25, -10);
	glVertex3i(10, -25, -10);
	glEnd();

	//Right
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3i(-10, -5, 10);
	glVertex3i(10, -5, 10);
	glVertex3i(10, -25, 10);
	glVertex3i(-10, -25, 10);
	glEnd();

	//Right 2
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3i(-10, -25, 10);
	glVertex3i(-10, -25, -10);
	glVertex3i(-10, -5, -10);
	glVertex3i(-10, -5, 10);
	glEnd();

	//glPointSize(5);
	//glColor3f(1, 1, 1);
	//glBegin(GL_POINTS);
	//glVertex3i(-10, -5, 10);
	//glEnd();

	//glPointSize(5);
	//glColor3f(1, 1, 1);
	//glBegin(GL_POINTS);
	//glVertex3i(-10, -25, 10);
	//glEnd();

	//glPointSize(5);
	//glColor3f(1, 1, 1);
	//glBegin(GL_POINTS);
	//glVertex3i(-10, -5, 10);
	//glEnd();

	//glPointSize(5);
	//glColor3f(1, 1, 1);
	//glBegin(GL_POINTS);
	//glVertex3i(10, -25, -10);
	//glEnd();
}

void Camera() {
	glOrtho(-100, 100, -100, 100, -100, 237);
	gluLookAt(cameraMode, 20, 20, 0, 0, 0, 0, 1, 0);
}

void SetSpawnPoints() {

	float xPos = 0;
	float yPos = 80;

	for (int i = 0; i < carsCount; i++)
	{
		float randValue = 0 + rand() % ((1 + 1) - 0);

		if (randValue != 0) {
			cars[i].direction = 'r';
			xPos = -(rand() % 50 + 110);
		}
		else {
			cars[i].direction = 'l';
			xPos = +(rand() % 50 + 110);
		}

		cars[i].xPos = xPos;
		cars[i].yPos = yPos + (-20 * i);
		cars[i].velocity = rand() % stage + 1;
	}
}

void DrawCars() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < carsCount; i++)
	{
		DrawCar3D(i);
	}
}

void DrawCapybara() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	#pragma region Capybara

		glBegin(GL_QUADS);
		glColor3f(1, 0.75f, 0.20f);

		glVertex3f(7.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, -5);
		glVertex3f(-2.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, -5);
		glVertex3f(-2.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, 5);
		glVertex3f(7.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, 5);

		glVertex3f(7.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, 5);
		glVertex3f(-2.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, 5);
		glVertex3f(-2.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, -5);
		glVertex3f(7.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, -5);

		glVertex3f(7.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, 5);
		glVertex3f(-2.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, 5);
		glVertex3f(-2.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, 5);
		glVertex3f(7.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, 5);

		glVertex3f(7.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, -5);
		glVertex3f(-2.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, -5);
		glVertex3f(-2.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, -5);
		glVertex3f(7.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, -5);

		glVertex3f(-2.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, 5);
		glVertex3f(-2.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, -5);
		glVertex3f(-2.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, -5);
		glVertex3f(-2.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, 5);

		glVertex3f(7.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, -5);
		glVertex3f(7.5 + capybaraEntity.xPos, 2.5 + capybaraEntity.yPos, 5);
		glVertex3f(7.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, 5);
		glVertex3f(7.5 + capybaraEntity.xPos, -2.5 + capybaraEntity.yPos, -5);

		glEnd();

	#pragma endregion
}

void NewCar(int carIndex) {

	float randValue = 0 + rand() % ((1 + 1) - 0);

	if (randValue != 0) {
		cars[carIndex].direction = 'r';
		cars[carIndex].xPos = -(rand() % 50 + 110);
	}
	else {
		cars[carIndex].direction = 'l';
		cars[carIndex].xPos = +(rand() % 50 + 110);
	}

	//Change color
	cars[carIndex].rgb[0] = (1.0 - 0.0) * ((((float)rand()) / (float)RAND_MAX) / 0.9) + 0.1;
	cars[carIndex].rgb[1] = (1.0 - 0.0) * ((((float)rand()) / (float)RAND_MAX) / 0.9) + 0.1;
	cars[carIndex].rgb[2] = (1.0 - 0.0) * ((((float)rand()) / (float)RAND_MAX) / 0.9) + 0.1;

	cars[carIndex].velocity = rand() % stage + 1;
}

void CarsMove() {

	for (int i = 0; i < carsCount; i++)
	{
		if (cars[i].direction == 'r')
		{
			if (cars[i].spawn && cars[i].xPos <= 110) {

				//cars[i].xPos += 2;
				cars[i].xPos += cars[i].velocity;
			}
			else {
				NewCar(i);
				cars[i].spawn = false;
				cars[i].spawn = true;
			}
		}
		else if (cars[i].direction == 'l')
		{
			if (cars[i].spawn && cars[i].xPos >= -110) {

				//cars[i].xPos -= 2;
				cars[i].xPos -= cars[i].velocity;
			}
			else {
				NewCar(i);
				cars[i].spawn = false;
				cars[i].spawn = true;
			}
		}
	}
}

void DrawScene() {
	Camera();
	DrawCapybara();
	DrawCars();
	CarsMove();
}

void CheckStage() {
	if (capybaraEntity.yPos >= 120) {
		SetSpawnPoints();
		stage++;
		capybaraEntity.yPos = -120;
		cout << "Current stage: " << stage << endl;
	}
}

void Restart() {
	//Set game as default
	SetSpawnPoints();
	stage = 1;
	capybaraEntity.xPos = 0;
	capybaraEntity.yPos = -120;
}

void Init() {
	srand(time(NULL));

	//Player default's position
	capybaraEntity.xPos = 0;
	capybaraEntity.yPos = -100;

	for (int i = 0; i < carsCount; i++)
	{
		//Setting colors
		cars[i].rgb[0] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;
		cars[i].rgb[1] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;
		cars[i].rgb[2] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;

		for (int i = 0; i < carsCount; i++)
		{
			cars[i].velocity = (6 - 1) * ((((float)rand()) / (float)RAND_MAX)) + 1;
		}

		cars[i].spawn = true;
	}
}

void Collision() {

	////Debug cap collision pos
	//glPointSize(5);
	//glColor3f(0, 0, 1);
	//glBegin(GL_POINTS);
	//glVertex2f(capybaraEntity.xPos, capybaraEntity.yPos);
	//glEnd();

	////Debug cap collision pos
	//for (int i = 0; i < carsCount; i++)
	//{
	//	glPointSize(5);
	//	glColor3f(0, 0, 1);
	//	glBegin(GL_POINTS);
	//	glVertex2f(cars[i].xPos, -cars[i].yPos);
	//	glEnd();
	//}

	//Check if capybara and enemy position are the same, then reestart the game
	for (int i = 0; i < carsCount; i++)
	{
		if ((cars[i].xPos + (cars[i].xSize / 2) > capybaraEntity.xPos - 5 && cars[i].xPos - (cars[i].xSize / 2) < capybaraEntity.xPos + 5)
			&& (-cars[i].yPos + (cars[i].ySize / 2) > capybaraEntity.yPos - 5 && -cars[i].yPos - (cars[i].ySize / 2) < capybaraEntity.yPos + 5))
		{
			cout << "********************DEAD********************" << endl;
			cout << "Final points: " << stage << endl;
			Restart();
		}
	}
}

void DebugCapPosition() {
	cout << "----------------------------" << endl;
	cout << "Cap X pos: " << capybaraEntity.xPos << endl;
	cout << "Cap Y pos:	" << capybaraEntity.yPos << endl;
	cout << "----------------------------" << endl;
}

static void error_callback(int error, const char* deion)
{
	fputs(deion, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Game control
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		Restart();
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		if (cameraMode == 2) {
			cameraMode = 0;
		}
		else {
			cameraMode = 2;
		}
	}

	//Capybara control
	if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_PRESS)
	{
		CheckStage();
		capybaraEntity.yPos += 20;

		//DebugCapPosition();
	}
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_PRESS)
	{
		if (capybaraEntity.yPos >= -80)
			capybaraEntity.yPos -= 20;

		//DebugCapPosition();
	}
	if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) && action == GLFW_PRESS)
	{
		if (capybaraEntity.xPos >= -60)
			capybaraEntity.xPos -= 20;

		//DebugCapPosition();
	}
	if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) && action == GLFW_PRESS)
	{
		if (capybaraEntity.xPos >= 80)
			capybaraEntity.xPos -= 20;

		capybaraEntity.xPos += 20;
		//DebugCapPosition();
	}
}

int main()
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "Capybara road", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, key_callback);

	Init();
	SetSpawnPoints();

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(0.3, 0.8, 0.6, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		DrawScene();
		Collision();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}
