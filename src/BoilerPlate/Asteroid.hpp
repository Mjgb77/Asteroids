#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_

#include "SpaceObject.hpp"


enum AsteroidSize { SMALL, MEDIUM, BIG };

class Asteroid : public SpaceObject {

public:
	/*CONSTRUCTOR*/
	Asteroid(AsteroidSize, Game *);

	/*PUBLIC FUNCTIONS*/

	AsteroidSize getSize();

	Asteroid* getAsteroidOfLessSize();
	
	void Render() override;

private:
	/*PRIVATE MEMBERS*/
	AsteroidSize m_asteroidSize;
};

#endif // ! ASTEROID_HPP_ 
