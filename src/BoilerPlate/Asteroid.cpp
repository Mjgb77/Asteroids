#include "Asteroid.hpp"
#include "Vector2.hpp"
#include "MathUtilities.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <vector>
#include <cmath>
#include <ctime>
#include <cstdio>

std::vector <Vector2> asteroidPoints;


Asteroid::Asteroid (AsteroidSize _size, int width, int height)
	: SpaceObject(width,height), m_asteroidSize(_size)
{
	position = new Vector2(MathUtilities::RandInt(width)-width/2, MathUtilities::RandInt(height) - height/2);
	m_rotAng = MathUtilities::Interpolate(0.0f, MathUtilities::PI * 2.0f, MathUtilities::RandFloat());
	
	asteroidPoints.push_back({ 0.0f, 15.0f });
	asteroidPoints.push_back({ 5.9f, 13.8f });
	asteroidPoints.push_back({ 12.0f, 6.0f });
	asteroidPoints.push_back({ 12.82f, 7.78f });
	asteroidPoints.push_back({ 14.92f, -1.57f });
	asteroidPoints.push_back({ 12.63f, -8.08f });
	asteroidPoints.push_back({ 5.35f, -13.96f });
	asteroidPoints.push_back({ -1.73f, -14.9f });
	asteroidPoints.push_back({ -5.0f, -10.0f });
	asteroidPoints.push_back({ -11.0f, -10.0f });
	asteroidPoints.push_back({ -14.77f, -2.63f });
	asteroidPoints.push_back({ -13.61f, 6.3f });
	asteroidPoints.push_back({ -10.69f, 10.52f });
}


AsteroidSize Asteroid::getSize() {
	return m_asteroidSize;
}

void Asteroid::Update() {
	position->x += 2.0f*cos(m_rotAng + 0.5f*MathUtilities::PI);
	position->y += 2.0f*sin(m_rotAng + 0.5f*MathUtilities::PI);

	WarpPosition();
}

void Asteroid::Render() {

	glLoadIdentity();
	glTranslatef(position->x, position->y, 0.0f);
	glRotatef(MathUtilities::ToDeg(m_rotAng), 0.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	for (Vector2 P : asteroidPoints) {
		P = P * (2.0f*static_cast<float> (m_asteroidSize) + 1.0f);
		glVertex2f(P.x, P.y);
	}
	glEnd();

}
