#include <iostream>
#include "Render.h"
using namespace std;

float xMin = -1.0, xMax = 1.0, yMin = -1.0, yMax = 1.0;

float posx = 0;
float posy = 20;
float posz = 20;

float alvox = 0.0;
float alvoy = 0.0;
float alvoz = 0.0;

float ang = 0.0;
float angX = 0.0;
float angY = 0.0;
float angZ = 0.0;

float moveX;
float moveY;

void View() {

	glOrtho(-100, 100, -100, 100, 1, 120);

	//Posição da camera
	gluLookAt(posx, posy, posz, alvox, alvoy, alvoz, 0, 1, 0);
}

void DrawCapybara() {
	//Comandos para habilitar a transparencia em areas sobrepostas
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Faces
	glBegin(GL_QUADS);
	glColor3f(0.0f + moveX, 0.0f + moveY, 1.0f);
	glVertex3i(-10 + moveX, -5 + moveY, -10);
	glVertex3i(10 + moveX, -5 + moveY, -10);
	glVertex3i(10 + moveX, -5 + moveY, 10);
	glVertex3i(-10 + moveX, -5 + moveY, 10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f + moveX, 0.0f + moveY, 0.0f, 0.5);
	glVertex3i(10 + moveX, -5 + moveY, -10);
	glVertex3i(10 + moveX, -5 + moveY, 10);
	glVertex3i(0 + moveX, 15 + moveY, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0f + moveX, 1.0f + moveY, 0.0f, 0.5);
	glVertex3i(10 + moveX, -5 + moveY, 10);
	glVertex3i(-10 + moveX, -5 + moveY, 10);
	glVertex3i(0 + moveX, 15 + moveY, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0f + moveX, 0.0f + moveY, 1.0f, 0.5);
	glVertex3i(-10 + moveX, -5 + moveY, -10);
	glVertex3i(10 + moveX, -5 + moveY, -10);
	glVertex3i(0 + moveX, 15 + moveY, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.1f + moveX, 0.22f + moveY, 0.5f, 0.5);
	glVertex3i(-10 + moveX, -5 + moveY, -10);
	glVertex3i(-10 + moveX, -5 + moveY, 10);
	glVertex3i(0 + moveX, 15 + moveY, 0);
	glEnd();
}

void DrawScene() {

	View();
	glTranslatef(0, 0, 0);

	DrawCapybara();
}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Angle control
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		ang += 10;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		ang -= 10;

	//Capybara control
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveY += 10;
		cout << moveY << endl;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		moveY -= 10;
		cout << moveY << endl;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		moveX -= 10;
		cout << moveX << endl;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		moveX += 10;
		cout << moveX << endl;
	}
}

int main()
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "First 3D", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		DrawScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}