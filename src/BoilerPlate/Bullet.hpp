#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "SpaceObject.hpp"

const float SHOT_FORCE = 10.0f;

class Bullet : public SpaceObject {

	friend class Player;
	int m_lifeTime;
public:
	Bullet(Game *);
	bool IsLifeTimeEnded();

	void Update(float);
	void Render() override;
};

#endif "BULLET_HPP_"
