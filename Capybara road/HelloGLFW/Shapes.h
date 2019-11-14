#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <ctime>

const float Pi = 3.14159;

class Shape
{
public:
	Shape() {}
	~Shape() {}
	void DrawCircle(float posX, float posY, float radius, float nPoints);
	void DrawTriangle();
};
