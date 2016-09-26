#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <algorithm>
#include <math.h>

const int width = 640;   const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawThick(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 3] = red;
	pixels[(i + width* j) * 3 + 6] = red;

	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 4] = green;
	pixels[(i + width* j) * 3 + 7] = green;

	pixels[(i + width* j) * 3 + 2] = blue;
	pixels[(i + width* j) * 3 + 5] = blue;
	pixels[(i + width* j) * 3 + 8] = blue;
};

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawThickLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawThick(i, j, red, green, blue);
	}
}

bool isInsideCircle(const double x, const double y)
{
	const double x_c = 500;
	const double y_c = 100;
	const double r = 80;

	const double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r * r;

	if (f < 80 && f > -80) return true;
	else return false;
}

bool isInsideCircleCor(double xcor, double ycor, double x, const double y)
{
	const double r = 50;
	const double f = (x - xcor)*(x - xcor) + (y - ycor)*(y - ycor) - r * r;
	if (f < 160 && f > -160) return true;
	else return false;
}

bool isInsideCircleCorsmall(double xcor, double ycor, double x, const double y)
{
	const double r = 20;
	const double f = (x - xcor)*(x - xcor) + (y - ycor)*(y - ycor) - r * r;
	if (f < 60 && f > -60) return true;
	else return false;
}


bool isInsideCircleCorarea(double xcor, double ycor, double x, const double y)
{
	const double r = 50;
	const double f = (x - xcor)*(x - xcor) + (y - ycor)*(y - ycor) - r * r;
	if (f < 150) return true;
	else return false;
}

void drawrebigcircle(double x1, double y1, double xpos, double ypos)
{
	for (int x = 0; x < 640; x++) for (int y = 0; y < 480; y++)
	{
		if (isInsideCircleCor(x1, y1, x, y) == true)
		{
			if (isInsideCircleCorarea(x1, y1, xpos, 480 - ypos) == true) drawPixel(x, y, 0.0f, 0.0f, 1.0f);
			else drawPixel(x, y, 1.0f, 0.0f, 0.0f);
		}
	}
}

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())return -1; window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	std::fill_n(pixels, width*height * 3, 1.0f);

	double xpos, ypos;





	while (!glfwWindowShouldClose(window))
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		for (int i = 330; i < 380; i++) drawThick(i - 280, i, 1.0f, 0.0f, 0.0f);
		// thick line
		for (int x = 0; x < 640; x++) for (int y = 0; y < 480; y++)
		{
			if (isInsideCircleCor(75, 350, x, y) == true)
			{
				if (isInsideCircleCorarea(75, 350, xpos, 480 - ypos) == true) drawPixel(x, y, 0.0f, 0.0f, 1.0f);
				else drawPixel(x, y, 1.0f, 0.0f, 0.0f);
			}
		}
		// thick line circle


		for (int x = 0; x < 640; x++) for (int y = 0; y < 480; y++)
		{
			if (isInsideCircleCorsmall(210, 350, x, y) == true)
			{
				drawPixel(x, y, 1.0f, 0.0f, 0.0f);
			}
		}
		// small circle
		for (int x = 0; x < 640; x++) for (int y = 0; y < 480; y++)
		{
			if (isInsideCircleCor(210, 350, x, y) == true)
			{
				if (isInsideCircleCorarea(210, 350, xpos, 480 - ypos) == true) drawPixel(x, y, 0.0f, 0.0f, 1.0f);
				else drawPixel(x, y, 1.0f, 0.0f, 0.0f);
			}
		}
		// small circle enclosing circle





		drawLine(320, 370, 360, 370, 1.0f, 0.0f, 0.0f);
		drawLine(320, 330, 360, 330, 1.0f, 0.0f, 0.0f);
		for (int i = 330; i < 370; i++)
		{
			drawPixel(320, i, 1.0f, 0.0f, 0.0f);
		}
		for (int i = 330; i < 370; i++)
		{
			drawPixel(360, i, 1.0f, 0.0f, 0.0f);
		} // rectangle
		drawrebigcircle(340, 350, xpos, ypos);








		drawLine(430, 330, 470, 380, 1.0f, 0.0f, 0.0f);
		drawLine(430, 380, 470, 330, 1.0f, 0.0f, 0.0f);
		drawrebigcircle(450, 350, xpos, ypos);
		// X shape





		for (int i = 330; i < 380; i++)
		{
			drawPixel(570, i, 1.0f, 0.0f, 0.0f);
		}
		drawLine(550, 350, 570, 330, 1.0f, 0.0f, 0.0f);
		drawLine(570, 330, 590, 350, 1.0f, 0.0f, 0.0f);
		drawrebigcircle(570, 350, xpos, ypos);
		// down arrow 




		drawLine(50, 150, 95, 150, 1.0f, 0.0f, 0.0f);
		drawLine(80, 170, 95, 150, 1.0f, 0.0f, 0.0f);
		drawLine(80, 130, 95, 150, 1.0f, 0.0f, 0.0f);
		drawrebigcircle(75, 150, xpos, ypos);
		// right arrow



		drawLine(200, 150, 223, 150, 1.0f, 0.0f, 0.0f);

		drawLine(182, 120, 212, 180, 1.0f, 0.0f, 0.0f);
		drawLine(212, 180, 238, 120, 1.0f, 0.0f, 0.0f);
		drawrebigcircle(210, 150, xpos, ypos);
		// big A


		for (int i = 130; i < 180; i++)
		{
			drawPixel(340, i, 1.0f, 0.0f, 0.0f);
		}
		drawrebigcircle(340, 150, xpos, ypos);
		// stick



		drawLine(430, 150, 470, 150, 1.0f, 0.0f, 0.0f);

		drawLine(430, 150, 450, 170, 1.0f, 0.0f, 0.0f);
		drawLine(430, 150, 450, 130, 1.0f, 0.0f, 0.0f);

		drawrebigcircle(450, 150, xpos, ypos);
		// left arrow




		drawLine(550, 160, 570, 180, 1.0f, 0.0f, 0.0f);
		drawLine(570, 180, 590, 160, 1.0f, 0.0f, 0.0f);
		for (int i = 130; i < 180; i++)
		{
			drawPixel(570, i, 1.0f, 0.0f, 0.0f);
		}
		drawrebigcircle(570, 150, xpos, ypos);
		// up arrow



		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		glfwSwapBuffers(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();
	delete[] pixels;
	return 0;
}

