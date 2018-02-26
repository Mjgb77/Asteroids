#include "Bullet.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "MathUtilities.hpp"

const int MAX_LIFE_TIME = 30;

Bullet::Bullet(Game* parent)
	: SpaceObject(parent) {
	m_lifeTime = 0;
	m_mass = 0.01f;
	m_radius = 3.0f;
}

bool Bullet::IsLifeTimeEnded() {
	return m_lifeTime > MAX_LIFE_TIME;
}

void Bullet::Update(float deltaTime) {
	SpaceObject::Update(deltaTime);
	m_lifeTime++;
}

void Bullet::Render() {
	glLoadIdentity();

	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(MathUtilities::ToDeg(m_rotAng), 0.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(-2.0, 2.0);
		glVertex2f(2.0, 2.0);
		glVertex2f(2.0, -2.0);
		glVertex2f(-2.0, -2.0);
	glEnd();

}