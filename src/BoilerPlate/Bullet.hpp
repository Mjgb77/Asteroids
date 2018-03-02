#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "SpaceObject.hpp"

const float SHOT_FORCE = 10.0f;

class Bullet : public SpaceObject {

	friend class Player;
	friend class Saucer;

public:
	/*CONSTRUCTOR*/
	Bullet(Game *);

	/*PUBLIC FUNCTIONS*/
	bool IsLifeTimeOver();

	void Update(float);
	void Render() override;

private:
	/*PRIVATE MEMBERS*/
	int m_lifeTime;
};

#endif // ! BULLET_HPP_
