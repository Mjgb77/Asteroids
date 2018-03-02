#include "Asteroid.hpp"

#include "MathUtilities.hpp"
#include "Vector2.hpp"

#include <vector>
#include <cmath>

#include "Game.hpp"
#include "Palette.hpp"
#include "DrawingTool.hpp"

class Game;

const float MAX_SPEED = 400.0f;
const float BORDER_WIDTH = 2.0f;

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

	DrawingTool::DrawLineLoop(asteroidPoints, m_position, Palette::White, BORDER_WIDTH, MathUtilities::ToDeg(m_rotAng), GetSizeFactor(m_asteroidSize) );

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
