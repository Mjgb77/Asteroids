#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_

#include "SpaceObject.hpp"


enum AsteroidSize { SMALL, MEDIUM, BIG };

class Asteroid : public SpaceObject {

public:
	Asteroid(AsteroidSize, int, int);

	AsteroidSize getSize();

	Asteroid* getAsteroidOfLessSize();
	
	void Render() override;

private:
	AsteroidSize m_asteroidSize;
};

#endif // ! ASTEROID_HPP_ 
