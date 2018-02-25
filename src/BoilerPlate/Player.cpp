#include "Player.hpp"
#include "MathUtilities.hpp"
#include "Vector2.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <vector>

std::vector <Vector2> shipPoints, thrusterPoints;

const float MAX_SPEED = 1000.0f;
const float OFFSET_ANG = 0.5f*MathUtilities::PI;
const int CHARGE_TIME = 10;

Player::Player(int width, int height)
	: SpaceObject(width, height), isThrusting(false) 
{
	charge = CHARGE_TIME;
	m_position = Vector2(Vector2::Origin);
	m_rotAng = OFFSET_ANG;
	m_radius = 20.0f;

	shipPoints.push_back({ 25.0f, 0.0f });
	shipPoints.push_back({ -15.0f, 20.0f });
	shipPoints.push_back({ -5.0f, 7.0f });
	shipPoints.push_back({ -5.0f, -7.0f });
	shipPoints.push_back({ -15.0f, -20.0f });
	
	thrusterPoints.push_back({ -10.0f , 5.0f });
	thrusterPoints.push_back({ -12.0f, 8.0f });
	thrusterPoints.push_back({ -11.0f, 5.0f });
	thrusterPoints.push_back({ -15.f, 10.0f });
	thrusterPoints.push_back({ -14.0f, 5.0f });
	thrusterPoints.push_back({ -19.0f, 10.0f });
	thrusterPoints.push_back({ -17.0f, 6.0f });
	thrusterPoints.push_back({ -23.5f, 9.0f });
	thrusterPoints.push_back({ -22.0f, 7.0f });
	thrusterPoints.push_back({ -28.0f, 9.0f });
	thrusterPoints.push_back({ -24.0f, 5.0f });
	thrusterPoints.push_back({ -27.0f, 3.0f });
	thrusterPoints.push_back({ -40.0f, 0.0f });
	thrusterPoints.push_back({ -27.0f, -3.0f });
	thrusterPoints.push_back({ -24.0f, -5.0f });
	thrusterPoints.push_back({ -28.0f, -9.0f });
	thrusterPoints.push_back({ -22.0f, -7.0f });
	thrusterPoints.push_back({ -23.5f, -9.0f });
	thrusterPoints.push_back({ -17.0f, -6.0f });
	thrusterPoints.push_back({ -19.0f, -10.0f });
	thrusterPoints.push_back({ -14.0f, -5.0f });
	thrusterPoints.push_back({ -15.f, -10.0f });
	thrusterPoints.push_back({ -11.0f , -5.0f });
	thrusterPoints.push_back({ -12.0f, -8.0f });
	thrusterPoints.push_back({ -10.0f, -5.0f });

}


void Player::MoveForward() {
	Vector2 impulse = Vector2(cos(m_rotAng), sin(m_rotAng))*12.0f;
	m_velocity += impulse * (1.0f / m_mass);
	WarpPosition();
}

void Player::RotateLeft(float deltaTime) {
	m_rotAng += deltaTime*7;
}

void Player::RotateRight(float deltaTime) {
	m_rotAng -= deltaTime*7;
}

void Player::StartThrust() {
	isThrusting = true;
}

static int blink = false;
void Player::StopThrust() {
	isThrusting = false;
	blink = 0;
}

bool Player::IsRecharged() {
	return charge == CHARGE_TIME;
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

	if (charge < CHARGE_TIME) charge++;

	if (m_velocity.Length() > MAX_SPEED) {
		m_velocity.Normalize();
		m_velocity *= MAX_SPEED;
	}

	m_velocity *= 0.98f;

	SpaceObject::Update(deltaTime);
}

void Player::Render() {
	glLoadIdentity();

	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(MathUtilities::ToDeg(m_rotAng), 0.0f, 0.0f, 1.0f);

	DrawShip();
	if (isThrusting) DrawThrust();
}

Bullet * Player::Shot() {
	charge = 0;
	Bullet *newBullet = new Bullet(this, m_width, m_height);
	return newBullet;
}

void Player::Reset() {
	*this = Player(m_width, m_height);
}