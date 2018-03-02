#include "Saucer.hpp"

#include "MathUtilities.hpp"
#include "Vector2.hpp"
#include "Palette.hpp"
#include "DrawingTool.hpp"
#include "Game.hpp"
#include <vector>

std::vector <Vector2> saucerPoints;

/*CONSTANTS*/

const float OFFSET_ANG = 0.5f*MathUtilities::PI; //Starting direction of the ship
const float SAUCER_SPEED = 100.0f;
const float BORDER_WIDTH = 2.0f;
const int CHARGE_TIME = 60; //Units of time until Saucer is ready to fire

/**/

class Game;

//inline float GetSizeFactor(SaucerSize size) {
//	return 2.0f*static_cast<int>(size) + 1;
//}


/*CONSTRUCTOR*/
Saucer::Saucer(Game * parent)
	: SpaceObject(parent)
{
	m_horizontalDirection = MathUtilities::RandInt(2);
	float yPos = (parent->m_height)* (MathUtilities::RandFloat()) + parent->m_minY;
	m_radius = 15.0f;

	m_isAlive = true;

	m_position = Vector2(parent->m_maxX,yPos);
	m_rotAng = MathUtilities::PI;
	if (m_horizontalDirection) m_position.x = parent->m_minX, m_rotAng = 0.0f;

	Vector2 initialImpulse = Vector2(cos(m_rotAng), sin(m_rotAng)) * SAUCER_SPEED;
	m_velocity = initialImpulse / m_mass;

	saucerPoints = GetPointsFrom("SaucerPoints.txt");
}

/*PUBLIC FUNCTIONS*/


bool Saucer::IsReadyToShot() {
	return m_charge >= CHARGE_TIME;
}

bool Saucer::IsAlive()
{
	return m_isAlive;
}

void Saucer::Update(float deltaTime) {

	if (!IsReadyToShot()) m_charge++;
	SpaceObject::Update(deltaTime);
}

void Saucer::Render() {

	DrawingTool::DrawLineLoop(saucerPoints, m_position, Palette::White, BORDER_WIDTH, 0.0f);
}


void Saucer::Kill() {
	m_isAlive = false;
}

Bullet * Saucer::Shot() {
	m_charge = 0; //Reset Charge 
	Bullet *newBullet = new Bullet(m_parent);
	newBullet->m_position = m_position;
	newBullet->m_rotAng = MathUtilities::RandFloat() * MathUtilities::PI * 2.0f;

	Vector2 impulse = Vector2(cos(newBullet->m_rotAng), sin(newBullet->m_rotAng)) * SHOT_FORCE;

	//Apply force to Bullet
	newBullet->m_velocity = impulse / newBullet->m_mass;
	newBullet->m_velocity += m_velocity;

	return newBullet;
}
