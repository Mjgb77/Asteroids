#include "ColorSetter.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

const Color ColorSetter::Amber = Color(1.0, 0.55, 0.0, 1.0);
const Color ColorSetter::Black = Color(0.0, 0.0, 0.0, 1.0);
const Color ColorSetter::Cyan = Color(0.1, 0.7, 0.9, 1.0);
const Color ColorSetter::Navy = Color(0.0, 0.0, 0.5, 1.0);
const Color ColorSetter::Red = Color(1.0, 0.0, 0.0, 1.0);

ColorSetter::ColorSetter(){
}

void ColorSetter::setBackground(Color color) {
	glClearColor(color.red, color.green, color.blue, color.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}




