#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Vector2.hpp"
#include "SpaceObject.hpp"
#include "Bullet.hpp"

const int MAX_NUMBER_OF_BULLETS = 4;

class Player : public SpaceObject {

	bool isThrusting;
	int charge;

public:

	Player(Game *);

	void MoveForward ();
	void RotateLeft(float);
	void RotateRight(float);
	
	void StartThrust ();
	void StopThrust ();

	bool IsReadyToShot();

	void Update(float);
	void Render() override;

	void Reset();
	Bullet * Shot();
};

#endif // !PLAYER_HPP_
