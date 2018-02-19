#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_

#include "Vector2.hpp"
#include "SpaceObject.hpp"

enum AsteroidSize {SMALL, MEDIUM, BIG };

class Asteroid : public SpaceObject {
	
	AsteroidSize m_asteroidSize;

public:
	Asteroid (AsteroidSize, int, int);

	AsteroidSize getSize();
	void Update() override;
	void Render() override;

};

#endif // ! ASTEROID_HPP_ 