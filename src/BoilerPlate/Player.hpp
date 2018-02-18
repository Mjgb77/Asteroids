#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Vector2.hpp"
#include "SpaceObject.hpp"

class Player : public SpaceObject {

	bool isThrusting;
	
public:
	Player(int, int);
;
	void MoveForward ();
	void RotateLeft();
	void RotateRight();
	
	void StartThrust ();
	void StopThrust ();

	void Update() override;
	void Render() override;

	bool isOnCollision (Vector2 *, float r);
};

#endif // !PLAYER_HPP_
