#include <iostream>
#include "Render.h"
using namespace std;

float xMin = -1.0, xMax = 1.0, yMin = -1.0, yMax = 1.0; 

float posx = 10.0;
float posy = 5.0;
float posz = 20.0;

float alvox = 0.0;
float alvoy = 0.0;
float alvoz = 0.0;

float ang = 0.0;
int proj = 0;

double zNear = 1;
double zFar = 120;
double zoom = 40;

void View() {

	//Tipo de camera
	if (proj == 0)
		glOrtho(-zoom, zoom, -zoom, zoom, zNear, zFar);
	else if (proj == 1)
		gluPerspective(140, 1, zNear, zFar);

	//Posição da camera
	gluLookAt(posx, posy, posz, alvox, alvoy, alvoz, 0, 1, 0);
}

void DrawPyramid(){
	//Comandos para habilitar a transparencia em areas sobrepostas
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Faces
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3i(-10, -5, -10);
	glVertex3i(10, -5, -10);
	glVertex3i(10, -5, 10);
	glVertex3i(-10, -5, 10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5);
	glVertex3i(10, -5, -10);
	glVertex3i(10, -5, 10);
	glVertex3i(0, 15, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0f, 1.0f, 0.0f, 0.5);
	glVertex3i(10, -5, 10);
	glVertex3i(-10, -5, 10);
	glVertex3i(0, 15, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0f, 0.0f, 1.0f, 0.5);
	glVertex3i(-10, -5, -10);
	glVertex3i(10, -5, -10);
	glVertex3i(0, 15, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.1f, 0.22f, 0.5f, 0.5);
	glVertex3i(-10, -5, -10);
	glVertex3i(-10, -5, 10);
	glVertex3i(0, 15, 0);
	glEnd();
}

void DrawScene() {

	View();
	glRotatef(ang, 0, 1, 0);
	glTranslatef(0, 0, 0);

	DrawPyramid();

	glTranslatef(10, 0, 10);
	glScalef(0.8, 0.8, 0.8);
	DrawPyramid();

	glTranslatef(-20, 0, 0);
	DrawPyramid();
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
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		ang += 10;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		ang -= 10;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		zoom = 40;

	//Camera zoom
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		if (zoom > 20)
			zoom -= 10;
		//zNear += 10;
		//zFar -= 10;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		zoom += 10;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		if (proj == 0)
			proj = 1;
		else
			proj = 0;
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