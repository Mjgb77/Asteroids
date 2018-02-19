#include "Player.hpp"
#include "MathUtilities.hpp"
#include "Vector2.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <vector>

std::vector <Vector2> shipPoints, thrusterPoints;


Player::Player(int width, int height)
	: SpaceObject(width, height), isThrusting(false) 
{
	position = new Vector2(Vector2::Origin);

	shipPoints.push_back({ 0.0f, 33.0f });
	shipPoints.push_back({ 30.0f, -27.0f });
	shipPoints.push_back({ 12.0f, -17.0f });
	shipPoints.push_back({ -12.0f, -17.0f });
	shipPoints.push_back({ -30.0f, -27.0f });

	thrusterPoints.push_back({ 12.0f, -20.0f });
	thrusterPoints.push_back({ 15.0f, -22.0f });
	thrusterPoints.push_back({ 11.0f, -21.0f });
	thrusterPoints.push_back({ 17.0f, -25.0f });
	thrusterPoints.push_back({ 10.0f, -24.0f });
	thrusterPoints.push_back({ 16.0f, -32.0f });
	thrusterPoints.push_back({ 8.0f, -26.0f });
	thrusterPoints.push_back({ 12.0f, -32.0f });
	thrusterPoints.push_back({ 10.0f, -30.0f });
	thrusterPoints.push_back({ 14.0f, -36.0f });
	thrusterPoints.push_back({ 6.0f, -32.0f });
	thrusterPoints.push_back({ 8.0f, -38.0f });
	thrusterPoints.push_back({ 0.0f, -55.0f });
	thrusterPoints.push_back({ -8.0f, -38.0f });
	thrusterPoints.push_back({ -6.0f, -32.0f });
	thrusterPoints.push_back({ -14.0f, -36.0f });
	thrusterPoints.push_back({ -10.0f, -30.0f });
	thrusterPoints.push_back({ -12.0f, -32.0f });
	thrusterPoints.push_back({ -8.0f, -26.0f });
	thrusterPoints.push_back({ -16.0f, -32.0f });
	thrusterPoints.push_back({ -10.0f, -24.0f });
	thrusterPoints.push_back({ -17.0f, -25.0f });
	thrusterPoints.push_back({ -11.0f, -21.0f });
	thrusterPoints.push_back({ -11.0f, -21.0f });
	thrusterPoints.push_back({ -15.0f, -22.0f });
	thrusterPoints.push_back({ -15.0f, -22.0f });
	thrusterPoints.push_back({ -12.0f, -20.0f });
}


void Player::MoveForward() {
	position->x += 10.0f*cos(m_rotAng + 0.5f*MathUtilities::PI);
	position->y += 10.0f*sin(m_rotAng + 0.5f*MathUtilities::PI);

	WarpPosition();
}

void Player::RotateLeft() {
	m_rotAng += 0.15f;
}

void Player::RotateRight() {
	m_rotAng -= 0.15f;
}

void Player::StartThrust() {
	isThrusting = true;
}

void Player::StopThrust() {
	isThrusting = false;
}

void DrawShip() {
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_POLYGON);
	
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
	glColor3f(0.9f, 0.6f, 0.13f);
	glBegin(GL_POLYGON);

	for (Vector2 P : thrusterPoints)
		glVertex2f(P.x, P.y);

	glEnd();

	glLineWidth(2.5f);
	glColor3f(1.0f, 0.15f, 0.0f);
	glBegin(GL_LINE_LOOP);

	for (Vector2 P : thrusterPoints)
		glVertex2f(P.x, P.y);

	glEnd();

}

void Player::Update() {
	//TODO:: Add inertia feature
}

void Player::Render() {
	glLoadIdentity();

	glTranslatef(position->x, position->y, 0.0f);
	glRotatef(MathUtilities::ToDeg(m_rotAng), 0.0f, 0.0f, 1.0f);

	DrawShip();
	if (isThrusting) DrawThrust();
}

