#ifndef PLAYER_H_
#define PLAYER_H_

#include "Vector2.h"
#include <vector>

using namespace std;

class Player {
	Vector2 * position;
	bool isThrusting;
	int width, height;

public:
	Player();
	//void Update();
	void Move(Vector2 &);
	void MoveForward ();
	void RotateLeft();
	void RotateRight();
	void Render ();
	void startThrust ();
	void stopThrust ();
	void warpPos ();
	void updateSize (int, int);
};

#endif // !PLAYER_H_
