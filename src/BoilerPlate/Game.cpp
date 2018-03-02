#include "Game.hpp"
#include "DrawingTool.hpp"
#include "Palette.hpp"
#include <vector>
#include "InputManager.hpp"
#include "SpaceObject.hpp"
#include "MathUtilities.hpp"

#include <sstream>

#include <irrKlang.h>

const int INITIAL_WAVE = 4;
const int GEN_SAUCER_TIME = 1000;
const int EXTRA_LIFE = (1 << 14);

/*CONSTRUCTOR/DESTRUCTOR*/

class SpaceObject;

Game::Game(int width, int height) : m_width(width), m_height(height), m_gameFont("../../fonts/font.ttf", 100) {
	m_maxX = 0.5f*m_width;
	m_minX = -m_maxX;
	
	m_maxY = 0.5f*m_height;
	m_minY = -m_maxY;
	
	m_currentAsteroidsW = INITIAL_WAVE;
	m_currentSaucerTime = 0;
	m_player = new Player(this);
	m_saucer = nullptr;

	InitializeSound();

	CreateAsteroids(m_currentAsteroidsW);
	
}

Game::~Game() {
	delete m_player;
	m_asteroids.clear();
	m_bullets.clear();
}

void Game::Reset() {
	m_currentAsteroidsW = INITIAL_WAVE;
	m_currentSaucerTime = 0;
	m_player = new Player(this);
	m_saucer = nullptr;
	m_bullets.clear();
	m_saucerBullets.clear();
	m_asteroids.clear();
	CreateAsteroids(m_currentAsteroidsW);
}

/*PUBLIC FUNCTIONS*/

void Game::UpdateSize(int width, int height) {
	m_width = width, m_height = height;
}

bool DEBUG_MODE = false;

void Game::Update(float deltaTime)
{
	if (m_player->GetLifes() == 0) {
		if (InputManager::Instance().IsKeyPressed('g')) {
			Reset();
		}
		return;
	}

	int lastScore = m_player->GetScore();
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


	if (m_asteroids.empty()) CreateAsteroids(++m_currentAsteroidsW);

	if (m_saucer) {
		m_saucer->Update(deltaTime);
		if (m_saucer->IsReadyToShot()) m_saucerBullets.push_back(m_saucer->Shot());
		if (CheckCollisionWithBullets(m_saucer)) m_saucer->Kill();
	}
	else {
		if (++m_currentSaucerTime == GEN_SAUCER_TIME) {
			m_currentSaucerTime = MathUtilities::RandInt(GEN_SAUCER_TIME);
			m_saucer = new Saucer(this);
		}
	}
	

	m_player->Update(deltaTime);
	for (auto bullet : m_bullets) bullet->Update(deltaTime);
	for (auto bullet : m_saucerBullets) bullet->Update(deltaTime);
	for (auto asteroid : m_asteroids) asteroid->Update(deltaTime);

	if (CheckCollisionWithSaucerBullets(m_player)) m_player->Explode();
	CheckCollisionOfAsteroids();
	CleanDeadBullets();

	if (m_saucer && !m_saucer->IsAlive()) m_saucer = nullptr;


	//Check for extra live
	if (lastScore / EXTRA_LIFE != m_player->GetScore() / EXTRA_LIFE) m_player->IncreaseLife();
}


void Game::Render()
{
	if (m_player->GetLifes() == 0) {
		DrawingTool::RenderText("PRESIONA G", m_gameFont, Palette::Cyan, m_minX+150.0f, 0.0f);
		return;
	}
	
	if (DEBUG_MODE) RenderDebug();

	DrawingTool::RenderText(GetScoreString(), m_gameFont, Palette::Cyan, m_minX + 50.0f, m_maxY - 100.0f);

	m_player->Render();

	for (auto bullet : m_bullets) bullet->Render();
	for (auto bullet : m_saucerBullets) bullet->Render();
	for (auto asteroid : m_asteroids) asteroid->Render();

	if (m_saucer) m_saucer->Render();
}

/*PRIVATE FUNCTIONS*/

void Game::InitializeSound() {
	m_bangSmallSound = new Sound("../../sounds/bangSmall.wav");
	m_bangMediumSound = new Sound("../../sounds/bangMedium.wav");
	m_bangLargeSound = new Sound("../../sounds/bangLarge.wav");

	m_extraShipSound = new Sound("../../sounds/extraShip.wav");
	m_fireSound = new Sound("../../sounds/fire.wav", 0.3f);
	m_thrusterSound = new Sound("../../sounds/thrust.wav");

	m_saucerSmallSound = new Sound("../../sounds/saucerSmall.wav");
	m_saucerBigSound = new Sound("../../sounds/saucerBig.wav");

	m_soundPlayer = new SoundPlayer();

	m_soundPlayer->AddSound(m_bangSmallSound);
	m_soundPlayer->AddSound(m_bangMediumSound);
	m_soundPlayer->AddSound(m_bangLargeSound);

	m_soundPlayer->AddSound(m_extraShipSound);
	m_soundPlayer->AddSound(m_fireSound);
	m_soundPlayer->AddSound(m_thrusterSound);

	m_soundPlayer->AddSound(m_saucerSmallSound);
	m_soundPlayer->AddSound(m_saucerBigSound);
}

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
	if (returnValue) m_player->IncreaseScore(tAsteroid->getSize() == SMALL ? 100 : (tAsteroid->getSize() == MEDIUM ? 50 : 20));
	return returnValue;
}

bool Game::CheckCollisionWithBullets(Saucer *tSaucer) {

	bool returnValue = false;

	for (auto bullet = m_bullets.begin(); bullet != m_bullets.end(); ) {
		if (tSaucer->HasCollisionWith(*bullet)) {
			bullet = m_bullets.erase(bullet);
			returnValue = true;
		}
		else bullet++;
	}
	if (returnValue) m_player->IncreaseScore(1000);
	return returnValue;
}

bool Game::CheckCollisionWithSaucerBullets(SpaceObject * tPlayer)
{
	bool returnValue = false;

	for (auto bullet = m_saucerBullets.begin(); bullet != m_saucerBullets.end(); ) {
		if (tPlayer->HasCollisionWith(*bullet)) {
			bullet = m_saucerBullets.erase(bullet);
			returnValue = true;
		}
		else bullet++;
	}
	return returnValue;
}

bool Game::CheckCollisionWithPlayer(Asteroid *tAsteroid) {
	if (tAsteroid->HasCollisionWith(m_player)) {
		m_player->Explode();
		return true;
	}
	return false;
}

bool Game::CheckCollisionWithSaucer(SpaceObject *tAsteroid) {
	if (!m_saucer) return false;
	
	if (tAsteroid->HasCollisionWith(m_saucer)) {
		m_saucer->Kill();
		return true;
	}
	return false;
}

void Game::CheckCollisionOfAsteroids() {
	std::list <Asteroid*> asteroidsToAdd;

	for (auto asteroid = m_asteroids.begin(); asteroid != m_asteroids.end(); ) {

		if (CheckCollisionWithBullets(*asteroid) || CheckCollisionWithPlayer(*asteroid) || CheckCollisionWithSaucer(*asteroid) || CheckCollisionWithSaucerBullets(*asteroid)) {
			if ((*asteroid)->getSize() != SMALL) {
				
				if ((*asteroid)->getSize() == BIG) m_soundPlayer->PlaySound(m_bangLargeSound);
				else m_soundPlayer->PlaySound(m_bangMediumSound);

				asteroidsToAdd.push_back((*asteroid)->getAsteroidOfLessSize());
				asteroidsToAdd.push_back((*asteroid)->getAsteroidOfLessSize());
			}
			else m_soundPlayer->PlaySound(m_bangSmallSound);
			
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
	for (auto bullet = m_saucerBullets.begin(); bullet != m_saucerBullets.end(); ) {
		if ((*bullet)->IsLifeTimeOver()) bullet = m_saucerBullets.erase(bullet);
		else bullet++;
	}
}

std::string Game::GetScoreString()
{
	std::stringstream ss;
	std::string score;
	ss << m_player->GetScore();
	ss >> score;
	return score;
}


void Game::ReadInput(float deltaTime) {
	/*THRUST*/
	static float sound = 0.1f;
	if (InputManager::Instance().IsKeyPressed(82)) {
		m_player->StartThrust();
		m_soundPlayer->PlaySound(m_thrusterSound, true);
	}
	if (InputManager::Instance().IsKeyReleased(82)) {
		m_player->StopThrust();
		m_soundPlayer->StopSound(m_thrusterSound);
	}


	/*SHOOT*/
	if (InputManager::Instance().IsKeyDown(32) && m_player->IsReadyToShot() && m_bullets.size() < MAX_NUMBER_OF_BULLETS) {
		m_bullets.push_back(m_player->Shot());
		m_soundPlayer->PlaySound(m_fireSound);
	}

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

	if (m_saucer) {
		m_saucer->Update(deltaTime);
		m_saucer->m_circleColor = Palette::White;
	}

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

		if (m_saucer) {
			if (asteroid->HasCollisionWith(m_saucer)) m_saucer->m_circleColor = Palette::Red, hasCollision = true;
		}

		if (asteroid->HasCollisionWith(m_player)) m_player->m_circleColor = Palette::Red, hasCollision = true;

		asteroid->m_circleColor = (hasCollision ? Palette::Red : Palette::White);
	}
}

void Game::RenderDebug() {

	/*DRAWING CIRCLES AROUND OBJECTS AND SEGMENT TO NEARBY ASTEROIDS*/
	m_player->DrawCircleAround();

	if (m_saucer) m_saucer->DrawCircleAround();

	for (auto asteroid : m_asteroids) {
		asteroid->DrawCircleAround();
		asteroid->DrawSegmentIfNearbyTo(m_player);
	}

	for (auto bullet : m_bullets) bullet->DrawCircleAround();

	/*DRAWING PLOT*/
	{
		const float xStart = m_width / 2 - 500.0f;
		const float yStart = 100.0f - m_height / 2;

		const float xScale = 1.5f;
		const float yScale = 1000.0f;

		std::vector<Vector2> plotPoints;
		for (int i = 0; i < plotLength; i++) plotPoints.push_back({ i * xScale, frameRate[i] * yScale });

		DrawingTool::DrawLineStrip(plotPoints, { xStart,yStart }, Palette::Red, 1.0f);

		std::vector<Vector2> referenceLine;
		referenceLine.push_back({ 0.0f, DESIRED_FRAME_TIME * yScale });
		referenceLine.push_back({ plotLength * xScale, DESIRED_FRAME_TIME * yScale });
		DrawingTool::DrawLineStrip(plotPoints, { xStart,yStart }, Palette::Cyan, 1.0f);

	}
}
