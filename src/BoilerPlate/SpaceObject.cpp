#include "SpaceObject.hpp"


SpaceObject::SpaceObject(int _width, int _height) : 
	width(_width), height(_height), mass(1.0f), rotAng(0.0f) {

}

void SpaceObject::WarpPos () {
	if (position->x > 0.5f*width) position->x -= width;
	if (position->y > 0.5f*height) position->y -= height;

	if (position->x < -0.5f*width) position->x += width;
	if (position->y < -0.5f*height) position->y += height;
}

void SpaceObject::UpdateSize(int newWidth, int newHeight) {
	width = newWidth, height = newHeight;
}