#include "Player.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	position = new Vector2();
}


void Player::Move (Vector2& unit) {
	position->x += unit.x;
	position->y += unit.y;
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
}


