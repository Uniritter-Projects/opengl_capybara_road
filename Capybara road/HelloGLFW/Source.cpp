#include <iostream>
#include "Render.h"
using namespace std;

struct enemy {
	int xPos;
	int yPos;
	char direction;
	float velocity;
};

struct capybara {
	int xPos;
	int yPos;
};

//Game
bool shoot;
int stage = 1;

//Capybara
capybara capybaraEntity;

//Enemies
const int enemiesCount = 10;
float enemyMove;
float randEnemyVelocity;
enemy enemies[enemiesCount];

void Camera() {
	glOrtho(-100, 100, -100, 100, -100, 250);
	gluLookAt(0, 20, 20, 0, 0, 0, 0, 1, 0);
}

void SpawnEnemies() {

	/* X pos can be -80 or +80
	 Y mus increase 20 by each point */

	float xPos = 0;
	float yPos = 0;

	for (int i = 0; i < enemiesCount; i++)
	{
		float randValue = 0 + rand() % ((1 + 1) - 0);

		if (randValue != 0) {
			enemies[i].direction = 'r';
			xPos = -80;
		}
		else {
			enemies[i].direction = 'l';
			xPos = +80;
		}

		enemies[i].xPos = xPos;
		enemies[i].yPos = yPos;

		yPos += 20;

		cout << "Spawn point " << i << endl;
		cout << "X:  " << xPos << endl;
		cout << "Y:  " << yPos << endl;
		cout << "----------" << endl;
	}
}

void DrawEnemies() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 0, 0, 1.0f);

	//Faces
	glBegin(GL_QUADS);
	glVertex3i(-10 + enemyMove, -5, -10);
	glVertex3i(10 + enemyMove, -5, -10);
	glVertex3i(10 + enemyMove, -5, 10);
	glVertex3i(-10 + enemyMove, -5, 10);
	glEnd();
}

void DrawCapybara() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma region Pyramid
	//Faces
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5);
	glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0f, 1.0f, 0.0f, 0.5);
	glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0f, 0.0f, 1.0f, 0.5);
	glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	glVertex3i(10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.1f, 0.22f, 0.5f, 0.5);
	glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, -10);
	glVertex3i(-10 + capybaraEntity.xPos, -5 + capybaraEntity.yPos, 10);
	glVertex3i(0 + capybaraEntity.xPos, 15 + capybaraEntity.yPos, 0);
	glEnd();
#pragma endregion
}

void DrawScene() {

	Camera();
	glTranslatef(0, 0, 0);

	DrawCapybara();

	glTranslatef(-88, 0, 0);
	DrawEnemies();

	//for (int i = 0; i < enemiesCount; i++)
	//{
	//	DrawEnemies();
	//	glTranslatef(-88, 0, 0);
	//}
}

void EnemiesMove() {
	//Enemy velocity must be between 0.5 and 2.5
	if (shoot && enemyMove <= 200) {
		enemyMove += randEnemyVelocity;
	}
	else {
		shoot = false;
		enemyMove = 0.0;
	}
}

void CheckStage() {
	if (capybaraEntity.yPos >= 120) {
		SpawnEnemies();
		stage++;
		capybaraEntity.yPos = -120;
		cout << "Current stage: " << stage << endl;
	}
}

void Reestart() {
	//Set game as defaul
	SpawnEnemies();
	stage = 1;
	capybaraEntity.xPos = 0;
	capybaraEntity.yPos = -120;
}

void Init() {
	//Player default's position
	capybaraEntity.xPos = 0;
	capybaraEntity.yPos = -100;
}

void Collision() {
	//Check if capybara and enemy position are the same, then reestart the game
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
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		if (capybaraEntity.yPos >= -80)
			capybaraEntity.yPos -= 20;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		if (capybaraEntity.xPos >= -60)
			capybaraEntity.xPos -= 20;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		if (capybaraEntity.xPos >= 80)
			capybaraEntity.xPos -= 20;

		capybaraEntity.xPos += 20;
	}
	if (key == GLFW_KEY_SPACE && !shoot) {
		//Mocking event to spawn enemy
		randEnemyVelocity = (2.5f - 0.5f) * ((((float)rand()) / (float)RAND_MAX)) + 0.5f;
		shoot = true;
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
	SpawnEnemies();

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
		EnemiesMove();
		Collision();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}