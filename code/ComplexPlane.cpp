#include <iostream>
#include <iomanip>
#include <vector>     
#include <complex> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT*m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
};

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x_size, y_size);
};

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x_size, y_size);
};

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
};

View ComplexPlane::getView()
{
	return m_view;
};
void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;

};
void ComplexPlane::loadText(Text& text)
{
	text.setCharacterSize(20);
	text.setFillColor(Color::White);
	text.setPosition(10, 10);

	stringstream x1, y1, x2, y2;
	float center_x, center_y, mouse_x, mouse_y;
	x1 << m_view.getCenter().x;
	x1 >> center_x;
	y1 << m_view.getCenter().y;
	y1 >> center_y;
	x2 << m_mouseLocation.x;
	x2 >> mouse_x;
	y2 << m_mouseLocation.y;
	y2 >> mouse_y;

	text.setString("Mandelbrot Set\nCenter: (" 
					+to_string(center_x) + "," + to_string(center_y) + ")"
					+"\nCursor: (" +to_string(mouse_x) + "," +to_string(mouse_y) + ")"
					+"\nLeft-click to Zoom in\nRight-click to Zoom out");
	
};
size_t ComplexPlane::countIterations(Vector2f coord)
{
	float x = coord.x;
	float y = coord.y;

	complex<double>c(x, y);
	complex<double>z(0.0);

	for (size_t i = 0; i < MAX_ITER; i++)
	{
		z = pow(z, 2) + c;
		if (abs(z) > 2)
			return i;
	}
	return MAX_ITER;
};
void ComplexPlane::iterationsToRGB(size_t iterations, Uint8& r, Uint8& g, Uint8& b) 
{
	if (iterations == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (iterations > 50)
	{
		r = 222 - (iterations % 17) * 5;
		g = 179 - (iterations % 17) * 5;
		b = 173;
	}
	else if (iterations > 30)
	{
		r = 222 - (iterations % 17) * 5;
		g = 0;
		b = 123;
	}
	else if (iterations > 15)
	{
		r = 185 - (iterations % 17) * 5;
		g = 92 - (iterations % 17) * 5;
		b = 80;
	}
	else
		r = 59 + (iterations % 17) * 5;
		g = 20;
		b = 40;
};