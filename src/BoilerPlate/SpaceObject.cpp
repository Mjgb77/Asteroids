#include "SpaceObject.hpp"
#include "MathUtilities.hpp"

#include "Game.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <cstdio>

/*PUBLIC FUNCTIONS*/
SpaceObject::SpaceObject(Game * parent) : 
	m_parent(parent), m_mass(1.0f), m_rotAng(0.0f) {
}


bool SpaceObject::HasCollisionWith(SpaceObject * obj)
{
	float dis = (obj->m_position - m_position).SquaredLength();
	float radioSum = m_radius + obj->m_radius;
	return dis < radioSum*radioSum;
}

void SpaceObject::Update(float deltaTime) {
	static int count = 0;
	m_position += (m_velocity * deltaTime);

	WarpPosition();
}

/*DEBUGGING FUNCTIONS*/

const float NEARBY_DISTANCE = 300;

void SpaceObject::DrawCircleAround() {
	const float PI2 = 2 * MathUtilities::PI;

	int lineAmount = 100;
	float delta = PI2 / lineAmount;
	
	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, 0.0f);
	glColor3f(m_circleColor.red, m_circleColor.green, m_circleColor.blue);
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	for (float ang = 0; ang < PI2; ang += delta) {
		glVertex2f(m_radius*cos(ang), m_radius*sin(ang));
	}
	glEnd();
}


void SpaceObject::DrawSegmentIfNearbyTo(SpaceObject * obj)
{
	float dis = (obj->m_position - m_position).SquaredLength();

	if (dis < NEARBY_DISTANCE * NEARBY_DISTANCE) {
		glLoadIdentity();
		glBegin(GL_LINE_STRIP);
		glVertex2f(m_position.x, m_position.y);
		glVertex2f(obj->m_position.x, obj->m_position.y);
		glEnd();
	}

}

/*PROTECTED FUNCTIONS*/
void SpaceObject::WarpPosition () {
	if (m_position.x > 0.5f*m_parent->m_width) m_position.x -= m_parent->m_width;
	if (m_position.y > 0.5f*m_parent->m_height) m_position.y -= m_parent->m_height;

	if (m_position.x < -0.5f*m_parent->m_width) m_position.x += m_parent->m_width;
	if (m_position.y < -0.5f*m_parent->m_height) m_position.y += m_parent->m_height;
}
