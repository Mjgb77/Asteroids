#include "Player.hpp"
#include "MathUtilities.hpp"
#include "Vector2.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <vector>

std::vector <Vector2> shipPoints, thrusterPoints;

/*CONSTANTS*/

/*This values will be affected by delta time*/
const float ACC_FORCE = 700.0f;
const float ROT_FORCE = 7.0f;
/**/

const float OFFSET_ANG = 0.5f*MathUtilities::PI; //Starting direction of the ship

const float MAX_SPEED = 1000.0f;

const float DRAG_FACTOR = 0.98f;
const int CHARGE_TIME = 5; //Units of time until Ship is ready to fire

/**/

/*CONSTRUCTOR*/
Player::Player(Game * parent)
	: SpaceObject(parent), isThrusting(false) 
{
	charge = CHARGE_TIME;
	m_position = Vector2(Vector2::Origin);
	m_rotAng = OFFSET_ANG;
	m_radius = 20.0f;

	shipPoints = GetPointsFrom("ShipPoints.txt");
	thrusterPoints = GetPointsFrom("ThrusterPoints.txt");
}

/*PUBLIC FUNCTIONS*/

void Player::MoveForward(float deltaTime) {
	Vector2 impulse = Vector2(cos(m_rotAng), sin(m_rotAng))*ACC_FORCE*deltaTime;
	m_velocity += impulse / m_mass;
	WarpPosition();
}

void Player::RotateLeft(float deltaTime) {
	m_rotAng += deltaTime*ROT_FORCE;
}

void Player::RotateRight(float deltaTime) {
	m_rotAng -= deltaTime*ROT_FORCE;
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

void DrawShip() {
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_FAN);

	for (Vector2 P : shipPoints)
		glVertex2f(P.x, P.y);
	
	glEnd();

	glLineWidth(2.0f);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_LINE_LOOP);

	for (Vector2 P : shipPoints)
		glVertex2f(P.x, P.y);

	glEnd();
}

void DrawThrust() {

	if (blink < 7) glColor3f(0.9f, 0.6f, 0.13f);
	else glColor3f(1.0, 0.4f, 0.01f);

	glBegin(GL_POLYGON);

	for (Vector2 P : thrusterPoints)
		glVertex2f(P.x, P.y);

	glEnd();

	if (blink < 7) {
		glLineWidth(2.5f);
		glColor3f(1.0f, 0.15f, 0.0f);
		glBegin(GL_LINE_LOOP);

		for (Vector2 P : thrusterPoints)
			glVertex2f(P.x, P.y);

		glEnd();
	}
	if (++blink == 12) blink = 0;
}

void Player::Update(float deltaTime) {

	if (!IsReadyToShot() ) charge++;

	if (m_velocity.Length() > MAX_SPEED) {
		m_velocity.Normalize();
		m_velocity *= MAX_SPEED;
	}

	m_velocity *= DRAG_FACTOR;

	SpaceObject::Update(deltaTime);
}

void Player::Render() {
	glLoadIdentity();

	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(MathUtilities::ToDeg(m_rotAng), 0.0f, 0.0f, 1.0f);

	DrawShip();
	if (isThrusting) DrawThrust();
}

void Player::Reset() {
	*this = Player(m_parent);
}

Bullet * Player::Shot() {
	charge = 0; //Reset Charge 
	Bullet *newBullet = new Bullet(m_parent);
	newBullet->m_position = m_position;
	newBullet->m_rotAng = m_rotAng;

	Vector2 impulse = Vector2(cos(m_rotAng), sin(m_rotAng)) * SHOT_FORCE;

	//Apply force to Bullet
	newBullet->m_velocity = impulse / newBullet->m_mass;
	newBullet->m_velocity += m_velocity;

	m_velocity -= impulse /m_mass; //Aply same force in opposite direction to ship
	return newBullet;
}
