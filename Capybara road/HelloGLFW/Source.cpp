#include <iostream>
#include "Render.h"
using namespace std;

struct car {
	char direction;
	int xPos;
	int yPos;
	float carMove;
	float velocity;
	bool spawn = true;
	float rgb[3] = { 0, 0, 0 };
};

struct capybara {
	int xPos;
	int yPos;
};

//Game mechanics
bool run;
int stage = 1;

//Capybara
capybara capybaraEntity;

//Cars
const int carsCount = 6;
float carMove;
float randCarVelocity;
car cars[carsCount];

void Camera() {
	glOrtho(-100, 100, -100, 100, -100, 250);
	gluLookAt(0, 20, 20, 0, 0, 0, 0, 1, 0);
}

void SpawnCars() {

	// X pos can be -80 or +80
	// Y mus increase 20 by each point
	// 10 cars

	float xPos = 0;
	float yPos = 70;

	for (int i = 0; i < carsCount; i++)
	{
		float randValue = 0 + rand() % ((1 + 1) - 0);

		if (randValue != 0) {
			cars[i].direction = 'r';
			xPos = -110;
		}
		else {
			cars[i].direction = 'l';
			xPos = +110;
		}

		cars[i].xPos = xPos;
		cars[i].yPos = yPos;

		yPos -= 40;

		//Debug spawn points
		//cout << "Spawn point " << i << endl;
		//cout << "X:  " << xPos << endl;
		//cout << "Y:  " << yPos << endl;
		//cout << "----------" << endl;
	}
}

void DrawCars() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0, 0, 0, 1.0f);

	for (int i = 0; i < carsCount; i++)
	{
		glColor4f(cars[i].rgb[0], cars[i].rgb[1], cars[i].rgb[2], 1.0f);

		glBegin(GL_QUADS);
		glVertex3i(cars[i].xPos + cars[i].carMove, -5, cars[i].yPos);
		glVertex3i((cars[i].xPos + 20) + cars[i].carMove, -5, cars[i].yPos);
		glVertex3i((cars[i].xPos + 20) + cars[i].carMove, -5, (cars[i].yPos + 20));
		glVertex3i(cars[i].xPos + cars[i].carMove, -5, (cars[i].yPos + 20));
		glEnd();
	}
}

void DrawCapybara() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma region Pyramid
	//Faces
	glBegin(GL_QUADS);
	glColor3f(0.25f, 0.1f, 0.13f);
	glVertex3i(-5 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -8);
	glVertex3i(5 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -8);
	glVertex3i(5 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 8);
	glVertex3i(-5 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 8);
	glEnd();

	//Old size (in case to collision study)
	//glBegin(GL_QUADS);
	//glColor3f(0.25f, 0.1f, 0.13f);
	//glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	//glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	//glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	//glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	//glEnd();

	//glBegin(GL_TRIANGLES);
	//glColor4f(1.0f, 0.0f, 0.0f, 0.5);
	//glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	//glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	//glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	//glEnd();

	//glBegin(GL_TRIANGLES);
	//glColor4f(0.0f, 1.0f, 0.0f, 0.5);
	//glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	//glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	//glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	//glEnd();

	//glBegin(GL_TRIANGLES);
	//glColor4f(0.0f, 0.0f, 1.0f, 0.5);
	//glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	//glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	//glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	//glEnd();

	//glBegin(GL_TRIANGLES);
	//glColor4f(0.1f, 0.22f, 0.5f, 0.5);
	//glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	//glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	//glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	//glEnd();
#pragma endregion
}

void DrawScene() {
	Camera();
	DrawCapybara();
	DrawCars();
}

void NewCar(int carIndex) {
	cars[carIndex].rgb[0] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;
	cars[carIndex].rgb[1] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;
	cars[carIndex].rgb[2] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;
	cars[carIndex].velocity = (2.5f - 0.5f) * ((((float)rand()) / (float)RAND_MAX)) + 0.5f;
}

void CarsMove() {

	for (int i = 0; i < carsCount; i++)
	{
		if (cars[i].direction == 'r')
		{
			if (cars[i].spawn && cars[i].carMove <= 250)
				cars[i].carMove += cars[i].velocity;
			else {
				//Receive new velocity
				NewCar(i);
				cars[i].spawn = false;
				cars[i].carMove = 0;
				cars[i].spawn = true;
			}
		}
		else if (cars[i].direction == 'l')
		{
			if (cars[i].spawn && cars[i].carMove >= -250)
				cars[i].carMove -= cars[i].velocity;
			else {
				//Receive new velocity
				NewCar(i);
				cars[i].spawn = false;
				cars[i].carMove = 0;
				cars[i].spawn = true;
			}
		}
	}
}

void CheckStage() {
	if (capybaraEntity.yPos >= 120) {
		SpawnCars();
		stage++;
		capybaraEntity.yPos = -120;
		cout << "Current stage: " << stage << endl;
	}
}

void Reestart() {
	//Set game as defaul
	SpawnCars();
	stage = 1;
	capybaraEntity.xPos = 0;
	capybaraEntity.yPos = -120;
}

void Init() {
	//Player default's position
	capybaraEntity.xPos = 0;
	capybaraEntity.yPos = -100;

	for (int i = 0; i < carsCount; i++)
	{
		cars[i].rgb[0] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;
		cars[i].rgb[1] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;
		cars[i].rgb[2] = (1 - 0) * ((((float)rand()) / (float)RAND_MAX)) + 0;

		cars[i].velocity = (2.5f - 0.5f) * ((((float)rand()) / (float)RAND_MAX)) + 0.5f;
		cars[i].spawn = true;
	}
}

void Collision() {

	//Debug collision pos
	//for (int i = 0; i < carsCount; i++)
	//{
	//	glPointSize(5);
	//	glColor3f(0, 0, 1);
	//	glBegin(GL_POINTS);
	//	glVertex2f(cars[i].xPos, cars[i].yPos);
	//	glEnd();
	//}

	//Check if capybara and enemy position are the same, then reestart the game
	for (int i = 0; i < carsCount; i++)
	{
		if ((cars[i].xPos == capybaraEntity.xPos || cars[i].xPos + 20 == capybaraEntity.xPos) && (cars[i].yPos + 10 == capybaraEntity.yPos))
		{
			//Restart();
			cout << "********************dead********************" << endl;
			cout << "Atropelada pelo carro " << i << endl;
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
		Reestart();
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//Capybara control
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		CheckStage();
		capybaraEntity.yPos += 20;

		//DebugCapPosition();
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		if (capybaraEntity.yPos >= -80)
			capybaraEntity.yPos -= 20;

		//DebugCapPosition();
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		if (capybaraEntity.xPos >= -60)
			capybaraEntity.xPos -= 20;

		//DebugCapPosition();
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
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
	SpawnCars();

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
		CarsMove();
		Collision();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}
