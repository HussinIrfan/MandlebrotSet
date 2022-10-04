#include <iostream>
#include <iomanip>
#include <vector>     
#include <complex> 
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;


int main()
{
	float width = VideoMode::getDesktopMode().width;
	float height = VideoMode::getDesktopMode().height;
	float aspectRatio = height / width;
	
	VideoMode vm(width, height);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	ComplexPlane cp(aspectRatio);
	Text text;
	Font font;
	//if (!font.loadFromFile("arial.ttf"))
	//{
		// error...
	//}

	VertexArray vArray;
	vArray.setPrimitiveType(Points);
	vArray.resize(width*height);
	
	enum class state{CALUCLATING, DISPLAYING};
	state state1 = state::CALUCLATING;

	Event event;
	Uint8 r, g, b;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape)) //Esc closes Program
			{
				window.close();
			}
			
		}
		if (state1 == state::CALUCLATING)
		{
			for (int j = 0; j < width; j++)
			{
				for (int i = 0; i < height; i++)
				{
					vArray[j + i*width].position = { (float)j,(float)i };
					size_t iterate = cp.countIterations(window.mapPixelToCoords({j,i}, cp.getView()));
					cp.iterationsToRGB(iterate, r, g, b);
					vArray[j + i * width].color = { r, g, b };
				}
			}
				
			state1 = state::DISPLAYING;
		}

		if (state1 == state::DISPLAYING)
		{
			window.clear();
			window.draw(vArray);
			window.display();
		}
	}

	return 0;
}