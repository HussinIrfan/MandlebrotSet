#include <complex.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <complex>
using namespace sf;

const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const unsigned int MAX_ITER = 64;
const float BASE_ZOOM = 0.5;

class ComplexPlane
{
public:
	ComplexPlane(float);
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2f);
	View getView();
	void setMouseLocation(Vector2f);
	void loadText(Text&);
	size_t countIterations(Vector2f);
	void iterationsToRGB(size_t, Uint8&, Uint8&, Uint8&);


private:
	Vector2f m_mouseLocation;
	View m_view;
	int m_zoomCount;
	float m_aspectRatio;

};
