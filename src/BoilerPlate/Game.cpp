#include "Game.hpp"
#include "Palette.hpp"
#include <vector>
#include "InputManager.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

/*CONSTRUCTOR/DESTRUCTOR*/
Game::Game(int width, int height) : m_width(width), m_height(height) {
	m_player = new Player(this);
	CreateAsteroids(5);
}

Game::~Game() {
	delete m_player;
	m_asteroids.clear();
	m_bullets.clear();
}

/*PUBLIC FUNCTIONS*/

void Game::UpdateSize(int width, int height) {
	m_width = width, m_height = height;
}

bool DEBUG_MODE = false;

void Game::Update(float deltaTime)
{
	/*CHECK DEBUG*/
	
	if (InputManager::Instance().IsKeyPressed('d')) DEBUG_MODE ^= 1; //IF DEBUG KEY IS PRESSED TOOGLE DEBUG MODE
	if (DEBUG_MODE) {
		UpdateDebug(deltaTime);
		return;
	}

	/*END CHECK DEBUG*/

	/*READ INPUT GAME*/
	ReadInput(deltaTime);

	/*UPDATE GAME MEMBERS*/
	m_player->Update(deltaTime);
	for (auto bullet : m_bullets) bullet->Update(deltaTime);
	for (auto asteroid : m_asteroids) asteroid->Update(deltaTime);
	
	CleanDeadBullets();

	CheckCollisionOfAsteroids();

}

void Game::Render()
{
	if (DEBUG_MODE) RenderDebug();

	m_player->Render();

	for (auto bullet : m_bullets) bullet->Render();
	for (auto asteroid : m_asteroids) asteroid->Render();
}

/*PRIVATE FUNCTIONS*/

void Game::CreateAsteroids(int count) {
	while (count--)
		m_asteroids.push_back(new Asteroid(BIG, this));
}

bool Game::CheckCollisionWithBullets(Asteroid *tAsteroid) {

	bool returnValue = false;
	
	for (auto bullet = m_bullets.begin(); bullet != m_bullets.end(); ) {
		if (tAsteroid->HasCollisionWith(*bullet)) {
			bullet = m_bullets.erase(bullet);
			returnValue = true;
		}
		else bullet++;
	}
	return returnValue;
}

bool Game::CheckCollisionWithPlayer(Asteroid *tAsteroid) {
	if (tAsteroid->HasCollisionWith(m_player)) {
		m_player->Reset();
		return true;
	}
	return false;
}

void Game::CheckCollisionOfAsteroids() {
	std::list <Asteroid*> asteroidsToAdd;

	for (auto asteroid = m_asteroids.begin(); asteroid != m_asteroids.end(); ) {

		if (CheckCollisionWithBullets(*asteroid) || CheckCollisionWithPlayer(*asteroid)) {
			if ((*asteroid)->getSize() != SMALL) {
				asteroidsToAdd.push_back((*asteroid)->getAsteroidOfLessSize());
				asteroidsToAdd.push_back((*asteroid)->getAsteroidOfLessSize());
			}
			asteroid = m_asteroids.erase(asteroid);
		}
		else asteroid++;
	}

	for (auto it : asteroidsToAdd) m_asteroids.push_back(it);

}

void Game::CleanDeadBullets() {
	for (auto bullet = m_bullets.begin(); bullet != m_bullets.end(); ) {
		if ((*bullet)->IsLifeTimeOver()) bullet = m_bullets.erase(bullet);
		else bullet++;
	}
}

void Game::ReadInput(float deltaTime) {
	/*THRUST*/
	if (InputManager::Instance().IsKeyPressed(82)) m_player->StartThrust();
	if (InputManager::Instance().IsKeyReleased(82)) m_player->StopThrust();

	/*SHOOT*/
	if (InputManager::Instance().IsKeyDown(32) && m_player->IsReadyToShot() && m_bullets.size() < MAX_NUMBER_OF_BULLETS) m_bullets.push_back(m_player->Shot());

	/*MOVEMENT*/
	if (InputManager::Instance().IsKeyDown(82)) m_player->MoveForward(deltaTime);
	if (InputManager::Instance().IsKeyDown(80)) m_player->RotateLeft(deltaTime);
	if (InputManager::Instance().IsKeyDown(79)) m_player->RotateRight(deltaTime);

}

/*DEBUGGING VARIABLES*/

int plotLength = 250;
float DESIRED_FRAME_TIME = 1.0f / 60;
std::vector <float> frameRate(plotLength, DESIRED_FRAME_TIME);

/*DEBUGGING FUNCTIONS*/

bool Game::DeleteAsteroid() {
	if (!m_asteroids.size()) return false; //If there are no Asteroid
	m_asteroids.pop_front();
	return true;
}

void Game::UpdateDebug(float deltaTime) {

	/*READ DEBUG INPUT*/
	if (InputManager::Instance().IsKeyPressed('c')) {
		CreateAsteroids(1);
		puts("New Asteroid created!");
	}
	if (InputManager::Instance().IsKeyReleased('x')) {
		if (DeleteAsteroid()) puts("An asteroid was deleted!");
		else puts("Attemp failed: THERE ARE NO ASTEROIDS");
	}

	/*READ GAME INPUT*/
	ReadInput(deltaTime);

	/*UPD PLOT FUNCTION*/
	static int time = 0;
	if (++time >= plotLength) time = 0;
	frameRate[time] = deltaTime;
	
	/*UPD GAME MEMBERS*/
	m_player->Update(deltaTime);

	m_player->m_circleColor = Palette::White;

	for (auto asteroid : m_asteroids) asteroid->Update(deltaTime);

	for (auto bullet : m_bullets) {
		bullet->Update(deltaTime);
		bullet->m_circleColor = Palette::White;
	}
	
	CleanDeadBullets();

	/*COLOR COLLISIONS*/

	for (auto asteroid : m_asteroids) {
		bool hasCollision = false;

		for (auto bullet : m_bullets) {
			if (asteroid->HasCollisionWith(bullet))
				bullet->m_circleColor = Palette::Red, hasCollision = true;
		}

		if (asteroid->HasCollisionWith(m_player)) m_player->m_circleColor = Palette::Red, hasCollision = true;
		
		asteroid->m_circleColor = (hasCollision ? Palette::Red : Palette::White);
	}
}

void Game::RenderDebug() {

	/*DRAWING CIRCLES AROUND OBJECTS AND SEGMENT TO NEARBY ASTEROIDS*/
	m_player->DrawCircleAround();

	for (auto asteroid : m_asteroids) {
		asteroid->DrawCircleAround();
		asteroid->DrawSegmentIfNearbyTo(m_player);
	}

	for (auto bullet : m_bullets) bullet->DrawCircleAround();

	/*DRAWING PLOT*/
	{
		const int xStart = m_width / 2 - 500;
		const int yStart = 100 - m_height / 2;

		const float xScale = 1.5f;
		const float yScale = 1000.0f;

		glLoadIdentity();
		glTranslatef(xStart, yStart, 0.0f);
		glColor3f(1.0f, 0.2f, 0.0f);
		glLineWidth(1.0f);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i < plotLength; i++)
			glVertex2f(i * xScale, frameRate[i] * yScale);

		glEnd();

		glColor3f(0.2f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		glVertex2f(0.0f, DESIRED_FRAME_TIME * yScale);
		glVertex2f(plotLength * xScale, DESIRED_FRAME_TIME * yScale);
		glEnd();
	}
}
