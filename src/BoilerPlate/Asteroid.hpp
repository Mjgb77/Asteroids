#include "Vector2.hpp"
#include "SpaceObject.hpp"

enum AsteroidSize {SMALL, MEDIUM, BIG };

class Asteroid : public SpaceObject {
	
	AsteroidSize asteroidSize;

public:
	Asteroid (AsteroidSize, int, int);

	AsteroidSize getSize();
	void Update() override;
	void Render() override;

};

