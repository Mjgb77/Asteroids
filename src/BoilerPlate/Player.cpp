#include "Player.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	position = new Vector2();
	isThrusting = false;
}


void Player::Move(Vector2& unit) {
	position->x += unit.x;
	position->y += unit.y;

	//WARP POSITION
	if (position->x > 0.5*width) position->x -= width;
	if (position->y > 0.5*height) position->y -= height;

	if (position->x < -0.5*width) position->x += width;
	if (position->y < -0.5*height) position->y += height;
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
	glVertex2d(0.0, -15.0);
	glVertex2d(-30.0, -30.0);
	glEnd();

	if (isThrusting) {
		glBegin(GL_LINE_LOOP);
		glVertex2d(20.0, -26.0);
		glVertex2d(0, -48.0);
		glVertex2d(-20.0, -26.0);
		glVertex2d(0.0, -15.0);
		glEnd();
	}
}
