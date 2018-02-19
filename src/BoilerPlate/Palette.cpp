#include "Palette.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

const Color Palette::Amber = Color(1.0f, 0.55f, 0.0f, 1.0f);
const Color Palette::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Palette::Cyan = Color(0.1f, 0.7f, 0.9f, 1.0f);
const Color Palette::DarkNight = Color(0.0f, 0.015f, 0.15f);
const Color Palette::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);

Palette::Palette(){
}

void Palette::SetBackground(Color color) {
	glClearColor(color.red, color.green, color.blue, color.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}




