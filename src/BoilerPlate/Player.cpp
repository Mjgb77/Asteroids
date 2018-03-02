#include "Player.hpp"

#include "Game.hpp"
#include "MathUtilities.hpp"
#include "Vector2.hpp"
#include "Palette.hpp"
#include "DrawingTool.hpp"

#include <vector>

std::vector <Vector2> shipPoints, thrusterPoints, explossionPoints;

/*CONSTANTS*/

/*This values will be affected by delta time*/
const float ACC_FORCE = 700.0f;
const float ROT_FORCE = 7.0f;
/**/

const float OFFSET_ANG = 0.5f*MathUtilities::PI; //Starting direction of the ship

const float MAX_SPEED = 1000.0f;

const float DRAG_FACTOR = 0.98f;
const int CHARGE_TIME = 7; //Units of time until Ship is ready to fire
const int RECOVERY_TIME = 120;

const float MAX_SCALE_EXPLOSSION = 15.0f;
/**/

class Game;

/*CONSTRUCTOR*/
Player::Player(Game * parent)
	: SpaceObject(parent), isThrusting(false)
{
	charge = CHARGE_TIME;
	currentRecovery = RECOVERY_TIME;
	m_position = Vector2(Vector2::Origin);
	m_rotAng = OFFSET_ANG;
	m_lifes = 3;
	m_score = 0;
	m_radius = 20.0f;

	shipPoints = GetPointsFrom("ShipPoints.txt");
	thrusterPoints = GetPointsFrom("ThrusterPoints.txt");
	explossionPoints = GetPointsFrom("ExplossionPoints.txt");
}

/*PUBLIC FUNCTIONS*/

int Player::GetLifes()
{
	return m_lifes;
}

int Player::GetScore()
{
	return m_score;
}

void Player::IncreaseScore(int score) {
	m_score += score;
}

void Player::IncreaseLife()
{
	m_lifes++;
}

void Player::MoveForward(float deltaTime) {
	if (currentRecovery < 0) return;
	Vector2 impulse = Vector2(cos(m_rotAng), sin(m_rotAng))*ACC_FORCE*deltaTime;
	m_velocity += impulse / m_mass;
	WarpPosition();
}

void Player::RotateLeft(float deltaTime) {
	if (currentRecovery < 0) return;
	m_rotAng += deltaTime * ROT_FORCE;
}

void Player::RotateRight(float deltaTime) {
	if (currentRecovery < 0) return;
	m_rotAng -= deltaTime * ROT_FORCE;
}

void Player::StartThrust() {
	isThrusting = true;
}

int blink = 0;

void Player::StopThrust() {
	isThrusting = false;
	blink = 0;
}

bool Player::IsReadyToShot() {
	return charge >= CHARGE_TIME;
}

void Player::DrawShip(Vector2 pos, float rotAng, float scale = 1.0f) {
	
	DrawingTool::DrawPolygon(shipPoints, pos, { 0.3f,0.3f,0.3f,1.0f }, MathUtilities::ToDeg(rotAng),scale);
	DrawingTool::DrawLineLoop(shipPoints, pos, Palette::White, 2.0f, MathUtilities::ToDeg(rotAng),scale);
	
}

int blinkExplossion = 0;
const int RATE = 12;
void Player::DrawThrust() {
	if (blinkExplossion < 8) {
		DrawingTool::DrawPolygon(thrusterPoints, m_position, Palette::Flame, MathUtilities::ToDeg(m_rotAng));
		DrawingTool::DrawLineLoop(thrusterPoints, m_position, Palette::Red, 3.0f, MathUtilities::ToDeg(m_rotAng));
	}
	else
		DrawingTool::DrawPolygon(thrusterPoints, m_position, { 1.0f, 0.4f, 0.01f, 1.0f }, MathUtilities::ToDeg(m_rotAng));


	if (++blinkExplossion == RATE) blinkExplossion = 0;
}

float C = 1.0;
void Player::DrawExplossion() {
	
	if (blinkExplossion < 8) {
		DrawingTool::DrawPolygon(explossionPoints, m_position, Palette::Flame, MathUtilities::ToDeg(m_rotAng), C);
		DrawingTool::DrawLineLoop(explossionPoints, m_position, Palette::Red, 10.0f, MathUtilities::ToDeg(m_rotAng), C);
	}
	else
		DrawingTool::DrawPolygon(explossionPoints, m_position, Palette::Amber, MathUtilities::ToDeg(m_rotAng), C);

	
	if (++blinkExplossion == RATE) blinkExplossion = 0;
}

void Player::Update(float deltaTime) {

	if (!IsReadyToShot()) charge++;
	if (currentRecovery < RECOVERY_TIME) currentRecovery++;

	if (m_velocity.Length() > MAX_SPEED) {
		m_velocity.Normalize();
		m_velocity *= MAX_SPEED;
	}

	m_velocity *= DRAG_FACTOR;

	SpaceObject::Update(deltaTime);
}

void Player::Render() {

	/*Rendering lifes*/
	float xStart = m_parent->m_minX + 50.0f;
	float yStart = m_parent->m_maxY -120.0f;
	for (int idShip = 0; idShip < m_lifes; idShip++, xStart += 30.0f) DrawShip({ xStart, yStart }, MathUtilities::PI * 0.5f, 0.5f);

	if (currentRecovery > 0 && currentRecovery < RECOVERY_TIME && (currentRecovery / 16) % 2 == 0) return;
	
	if (currentRecovery < 0) {
		DrawExplossion();
		C *= 1.07f;
		if (C > MAX_SCALE_EXPLOSSION) C = MAX_SCALE_EXPLOSSION;

	}
	else if (currentRecovery == 0) Reset();
	else {
		DrawShip(m_position, m_rotAng);
		C = 1.0;
		if (isThrusting) DrawThrust();
	}
}

void Player::Reset() {

	m_position = Vector2(Vector2::Origin);
	m_velocity = Vector2(Vector2::Origin);

	m_rotAng = OFFSET_ANG;

}

void Player::Explode() {
	if (currentRecovery < RECOVERY_TIME)  return;
	charge = -80;
	currentRecovery = -80;
	m_lifes--;
}

Bullet * Player::Shot() {
	charge = 0; //Reset Charge 
	Bullet *newBullet = new Bullet(m_parent);
	newBullet->m_position = m_position + (Vector2(cos(m_rotAng), sin(m_rotAng))*m_radius); //Position + Radius with ship direction
	newBullet->m_rotAng = m_rotAng;

	Vector2 impulse = Vector2(cos(m_rotAng), sin(m_rotAng)) * SHOT_FORCE;

	//Apply force to Bullet
	newBullet->m_velocity = impulse / newBullet->m_mass;
	newBullet->m_velocity += m_velocity;

	m_velocity -= impulse / m_mass; //Aply same force in opposite direction to ship
	return newBullet;
}
