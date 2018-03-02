#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "SpaceObject.hpp"
#include "Bullet.hpp"

const int MAX_NUMBER_OF_BULLETS = 4;

class Player : public SpaceObject {
	friend class Saucer;
public:
	/*CONSTRUCTOR*/
	Player(Game *);

	/*PUBLIC FUNCTIONS*/
	int GetLifes();
	int GetScore();

	void IncreaseScore(int);
	void IncreaseLife();

	void MoveForward (float);
	void RotateLeft(float);
	void RotateRight(float);
	
	void DrawShip(Vector2, float, float);
	void DrawExplossion();
	void DrawThrust();

	void StartThrust();
	void StopThrust ();

	bool IsReadyToShot();

	void Update(float);
	void Render() override;

	void Reset();
	void Explode();

	Bullet * Shot();

private:
	/*PRIVATE MEMBERS*/
	bool isThrusting;
	int charge;
	int currentRecovery;
	int m_lifes;
	int m_score;
};

#endif // !PLAYER_HPP_
