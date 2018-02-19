#include "SpaceObject.hpp"


SpaceObject::SpaceObject(int _width, int _height) : 
	m_width(_width), m_height(_height), m_mass(1.0f), m_rotAng(0.0f) {

}

void SpaceObject::WarpPosition () {
	if (position->x > 0.5f*m_width) position->x -= m_width;
	if (position->y > 0.5f*m_height) position->y -= m_height;

	if (position->x < -0.5f*m_width) position->x += m_width;
	if (position->y < -0.5f*m_height) position->y += m_height;
}

void SpaceObject::UpdateSize(int newWidth, int newHeight) {
	m_width = newWidth, m_height = newHeight;
}