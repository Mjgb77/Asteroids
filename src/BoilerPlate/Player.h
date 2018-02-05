#ifndef PLAYER_H_
#define PLAYER_H_

#include "Vector2.h"

class Player
{
	Vector2 * position;
public:
	Player();
	//void Update();
	void Move(Vector2 &);
	void Render();
};

#endif // !PLAYER_H_
