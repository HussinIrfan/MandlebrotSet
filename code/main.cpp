#include <iostream>
#include <vector>     
#include <complex> 
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;


int main()
{
	float width = VideoMode::getDesktopMode().width/2;
	float height = VideoMode::getDesktopMode().height/2;
	float aspectRatio = height / width;
	
	VideoMode vm(width, height);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	ComplexPlane cp(aspectRatio);
	Text text;
	Font font;
	if (!font.loadFromFile("font/RobotoMono-Medium.ttf"))
	{
		cout << "Error loading font..";
	}
	text.setFont(font);


	VertexArray vArray;
	vArray.setPrimitiveType(Points);
	vArray.resize(width*height);
	
	enum class state{CALCULATING, DISPLAYING};
	state state1 = state::CALCULATING;

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
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				cp.setCenter(window.mapPixelToCoords(Mouse::getPosition(window), cp.getView()));
				
				if (event.mouseButton.button == Mouse::Right)
				{
					cp.zoomOut();
					cout << "right button clicked" << endl;
				}
				if (event.mouseButton.button == Mouse::Left)
				{
					cp.zoomIn();
					cout << "left button clicked" << endl;
				}

				
				state1 = state::CALCULATING;
				if (state1 == state::CALCULATING)
					cout << "bool flipped" << endl;
			}

			if (event.type == Event::MouseMoved)
			{
				cp.setMouseLocation(window.mapPixelToCoords({event.mouseMove.x,event.mouseMove.y}, cp.getView()));
			}
			
		}

		if (state1 == state::CALCULATING)
		{
			cout << "calculating" << endl;
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
			//cp.loadText(text);
		}

		if (state1 == state::DISPLAYING)
		{
			cp.loadText(text);
			window.clear();
			window.draw(vArray);
			window.draw(text);
			window.display();
		}
	}

	return 0;
}