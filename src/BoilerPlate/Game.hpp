#ifndef GAME_HPP_
#define GAME_HPP_

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Font.hpp"
#include "Saucer.hpp"
#include "Player.hpp"
#include "SoundPlayer.hpp"
#include <list>

class Game
{
	friend class Saucer;
public:
	/*CONSTRUCTOR/DESTRUCTOR*/
	Game(int, int);
	~Game();

	/*PUBLIC MEMBERS*/
	int m_width, m_height;
	float m_minX, m_maxX;
	float m_minY, m_maxY;
	int m_currentAsteroidsW;


	/*PUBLIC FUNCTIONS*/
	void UpdateSize(int, int);
	void Update(float);
	void Render();

private:
	
	/*PRIVATE MEMBERS*/
	int m_currentSaucerTime;
	Font m_gameFont;

	Sound * m_bangSmallSound;
	Sound * m_bangMediumSound;
	Sound * m_bangLargeSound;

	Sound * m_extraShipSound;
	Sound * m_fireSound;
	Sound * m_thrusterSound;

	Sound * m_saucerSmallSound;
	Sound * m_saucerBigSound;
	
	SoundPlayer * m_soundPlayer;

	/*GAME OBJECTS*/
	Player * m_player;
	Saucer * m_saucer;
	std::list <Asteroid*> m_asteroids;
	std::list <Bullet*> m_bullets, m_saucerBullets;

	/*PRIVATE FUNCTIONS*/
	void InitializeSound();

	void CreateAsteroids(int);
	
	bool CheckCollisionWithBullets(Asteroid *);
	bool CheckCollisionWithBullets(Saucer *);
	bool CheckCollisionWithSaucerBullets(SpaceObject *);

	bool CheckCollisionWithPlayer(Asteroid *);
	bool CheckCollisionWithSaucer(SpaceObject *);
	void CheckCollisionOfAsteroids();
	
	void CleanDeadBullets();
	
	std::string GetScoreString();

	void ReadInput(float);

	/*DEBUGGING FUNCTIONS*/

	bool DeleteAsteroid();
	void UpdateDebug(float);
	void RenderDebug();

	void Reset();

};

#endif // !GAME_HPP_
