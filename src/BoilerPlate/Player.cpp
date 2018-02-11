#include "Player.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	position = new Vector2();
	isThrusting = false;
}

void Player::warpPos() {
	if (position->x > 0.5*width) position->x -= width;
	if (position->y > 0.5*height) position->y -= height;

	if (position->x < -0.5*width) position->x += width;
	if (position->y < -0.5*height) position->y += height;
}

void Player::Move(Vector2& unit) {
	position->x += unit.x;
	position->y += unit.y;

	warpPos();
}

void Player::MoveForward() {

}

void Player::RotateLeft() {

}


void Player::updateSize(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;
}


void Player::startThrust() {
	isThrusting = true;
}

void Player::stopThrust() {
	isThrusting = false;
}

void Player::Render() {
	glLoadIdentity();

	glTranslated(position->x, position->y, 0.0);

	glBegin(GL_LINE_LOOP);
	glVertex2d(0.0, 30.0);
	glVertex2d(30.0, -30.0);
	glVertex2d(12.0, -20.0);
	glVertex2d(-12.0, -20.0);
	glVertex2d(-30.0, -30.0);
	glEnd();

	if (isThrusting) {
		glBegin(GL_LINE_LOOP);
		glVertex2d(12.0, -20.0);
		glVertex2d(15.0, -22.0);
		glVertex2d(11.0, -21.0);
		glVertex2d(17.0, -25.0);
		glVertex2d(10.0, -24.0);
		glVertex2d(16.0, -32.0);
		glVertex2d(8.0, -26.0);
		glVertex2d(12.0, -32.0);
		glVertex2d(10.0, -30.0);
		glVertex2d(14.0, -36.0);
		glVertex2d(6.0, -32.0);
		glVertex2d(8.0, -38.0);
		glVertex2d(0.0, -55.0);
		glVertex2d(-8.0, -38.0);
		glVertex2d(-6.0, -32.0);
		glVertex2d(-14.0, -36.0);
		glVertex2d(-10.0, -30.0);
		glVertex2d(-12.0, -32.0);
		glVertex2d(-8.0, -26.0);
		glVertex2d(-16.0, -32.0);
		glVertex2d(-10.0, -24.0);
		glVertex2d(-17.0, -25.0);
		glVertex2d(-11.0, -21.0);
		glVertex2d(-11.0, -21.0);
		glVertex2d(-15.0, -22.0);
		glVertex2d(-15.0, -22.0);
		glVertex2d(-12.0, -20.0);
		glEnd();
	}
}
