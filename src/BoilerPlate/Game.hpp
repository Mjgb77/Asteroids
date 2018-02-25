#ifndef GAME_HPP_
#define GAME_HPP_

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include <list>

class Game
{
public:
	/*CONSTRUCTOR/DESTRUCTOR*/
	Game(int, int);
	~Game();

	/*PUBLIC FUNCTIONS*/
	void UpdateSize(int, int);
	void Update(float);
	void Render();

private:
	/*PRVIVATE MEMBERS*/
	int m_width, m_height;
	
	/*GAME OBJECTS*/
	Player * m_player;
	std::list <Asteroid*> m_asteroids;
	std::list <Bullet*> m_bullets;

	/*PRIVATE FUNCTIONS*/
	void CreateAsteroids(int);
	
	bool CheckCollisionWithBullets(Asteroid *);
	bool CheckCollisionWithPlayer(Asteroid *);
	
	void CleanDeadBullets();

	void ReadInput(float);

	/*DEBUGGING FUNCTIONS*/

	bool DeleteAsteroid();
	void UpdateDebug(float);
	void RenderDebug();

};

#endif // !GAME_HPP_
