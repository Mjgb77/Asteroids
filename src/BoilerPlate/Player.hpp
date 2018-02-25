#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Vector2.hpp"
#include "SpaceObject.hpp"
#include "Bullet.hpp"

const int MAX_NUMBER_OF_BULLETS = 5;

class Player : public SpaceObject {
	
	friend class Bullet;

	bool isThrusting;
	int charge;

public:

	Player(int, int);

	void MoveForward ();
	void RotateLeft(float);
	void RotateRight(float);
	
	void StartThrust ();
	void StopThrust ();

	bool IsRecharged();

	void Update(float);
	void Render() override;

	void Reset();
	Bullet * Shot();
};

#endif // !PLAYER_HPP_
