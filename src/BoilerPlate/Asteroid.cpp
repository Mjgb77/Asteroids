#include "Asteroid.hpp"

#include "MathUtilities.hpp"
#include "Vector2.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <vector>
#include <cmath>

#include "Game.hpp"

class Game;


const float MAX_SPEED = 400.0f;

std::vector <Vector2> asteroidPoints;

inline float GetSizeFactor(AsteroidSize size) {
	return 2.0f*static_cast<int>(size) + 1;
}

/*CONSTRUCTOR*/

Asteroid::Asteroid (AsteroidSize size, Game * parent)
	: SpaceObject(parent), m_asteroidSize(size)
{
	float sizeFactor = GetSizeFactor(size);
	
	m_mass = sizeFactor;
	m_radius = 15.0f*sizeFactor;
	
	m_rotAng = MathUtilities::RandFloat() * (2.0f * MathUtilities::PI); //Random float between (0.0, 2PI);
	m_position = Vector2(parent->m_width * (MathUtilities::RandFloat() - 0.5f), parent->m_height * (MathUtilities::RandFloat() - 0.5f)); //Random position within the game viewport
	
	Vector2 initialImpulse = Vector2(cos(m_rotAng), sin(m_rotAng)) * (MAX_SPEED * MathUtilities::RandFloat()); //Random vector force with magnitude between 0 and MAX_SPEED
	m_velocity = initialImpulse / m_mass;
	
	asteroidPoints = GetPointsFrom("AsteroidPoints.txt");
}


/*PUBLIC FUNCTIONS*/

AsteroidSize Asteroid::getSize() {
	return m_asteroidSize;
}

void Asteroid::Render() {

	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, 0.0f);
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

Asteroid * Asteroid::getAsteroidOfLessSize()
{
	if (m_asteroidSize == SMALL) return nullptr;
	
	int id = static_cast<int>(m_asteroidSize);
	AsteroidSize newSize = static_cast<AsteroidSize>(id - 1);
	
	Asteroid * newAsteroid = new Asteroid(newSize, m_parent);
	newAsteroid->m_position = m_position;

	return newAsteroid;
}
