#include "ColorSetter.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

const Color ColorSetter::Amber = Color(1.0f, 0.55f, 0.0f, 1.0f);
const Color ColorSetter::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color ColorSetter::Cyan = Color(0.1f, 0.7f, 0.9f, 1.0f);
const Color ColorSetter::DarkNight = Color(0.0f, 0.015f, 0.15f);
const Color ColorSetter::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);

ColorSetter::ColorSetter(){
}

void ColorSetter::setBackground(Color color) {
	glClearColor(color.red, color.green, color.blue, color.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}




