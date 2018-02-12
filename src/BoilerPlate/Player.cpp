#include "Player.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	position = new Vector2(Vector2::Origin);
	isThrusting = false;
}

void WarpPos(Vector2* position, int width, int height) {
	if (position->x > 0.5f*width) position->x -= width;
	if (position->y > 0.5f*height) position->y -= height;

	if (position->x < -0.5f*width) position->x += width;
	if (position->y < -0.5f*height) position->y += height;
}

void Player::Move(Vector2& unit) {
	position->x += unit.x;
	position->y += unit.y;

	WarpPos(position, width, height);
}

void Player::MoveForward() {
}

void Player::RotateLeft() {
}

void Player::RotateRight() {
}

void Player::StartThrust() {
	isThrusting = true;
}

void Player::StopThrust() {
	isThrusting = false;
}

void Player::UpdateSize(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;
}


void DrawShip() {
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0f, 30.0f);
	glVertex2f(30.0f, -30.0f);
	glVertex2f(12.0f, -20.0f);
	glVertex2f(-12.0f, -20.0f);
	glVertex2f(-30.0f, -30.0f);
	glEnd();
}

void DrawThrust() {
	glBegin(GL_LINE_LOOP);
	glVertex2f(12.0f, -20.0f);
	glVertex2f(15.0f, -22.0f);
	glVertex2f(11.0f, -21.0f);
	glVertex2f(17.0f, -25.0f);
	glVertex2f(10.0f, -24.0f);
	glVertex2f(16.0f, -32.0f);
	glVertex2f(8.0f, -26.0f);
	glVertex2f(12.0f, -32.0f);
	glVertex2f(10.0f, -30.0f);
	glVertex2f(14.0f, -36.0f);
	glVertex2f(6.0f, -32.0f);
	glVertex2f(8.0f, -38.0f);
	glVertex2f(0.0f, -55.0f);
	glVertex2f(-8.0f, -38.0f);
	glVertex2f(-6.0f, -32.0f);
	glVertex2f(-14.0f, -36.0f);
	glVertex2f(-10.0f, -30.0f);
	glVertex2f(-12.0f, -32.0f);
	glVertex2f(-8.0f, -26.0f);
	glVertex2f(-16.0f, -32.0f);
	glVertex2f(-10.0f, -24.0f);
	glVertex2f(-17.0f, -25.0f);
	glVertex2f(-11.0f, -21.0f);
	glVertex2f(-11.0f, -21.0f);
	glVertex2f(-15.0f, -22.0f);
	glVertex2f(-15.0f, -22.0f);
	glVertex2f(-12.0f, -20.0f);
	glEnd();
}

void Player::Render() {
	glLoadIdentity();

	glTranslatef(position->x, position->y, 0.0f);

	DrawShip();
	if (isThrusting) DrawThrust();
}
