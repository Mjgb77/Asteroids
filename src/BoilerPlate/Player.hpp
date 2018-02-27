#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "SpaceObject.hpp"
#include "Bullet.hpp"

const int MAX_NUMBER_OF_BULLETS = 4;

class Player : public SpaceObject {

public:
	/*CONSTRUCTOR*/
	Player(Game *);

	/*PUBLIC FUNCTIONS*/

	void MoveForward (float);
	void RotateLeft(float);
	void RotateRight(float);
	
	void StartThrust ();
	void StopThrust ();

	bool IsReadyToShot();

	void Update(float);
	void Render() override;

	void Reset();

	Bullet * Shot();

private:
	/*PRIVATE MEMBERS*/
	bool isThrusting;
	int charge;
};

#endif // !PLAYER_HPP_
