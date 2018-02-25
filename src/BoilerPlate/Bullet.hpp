#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "SpaceObject.hpp"
#include "Player.hpp"

class Player;

class Bullet : public SpaceObject {
	int m_lifeTime;
public:
	Bullet(Player*, int, int);
	bool IsLifeTimeEnded();

	void Update(float);
	void Render() override;
};

#endif "BULLET_HPP_"
