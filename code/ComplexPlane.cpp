#include <iostream>
#include <iomanip>
#include <vector>     
#include <complex> 
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
	//m_mouseLocation(coord);

};
void ComplexPlane::loadText(Text&)
{


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