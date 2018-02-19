#include "Color.hpp"
#include "MathUtilities.hpp"

Color::Color (float red, float green, float blue, float alpha) {
	this->red = MathUtilities::Clamp(red, 0.0f, 1.0f);
	this->green = MathUtilities::Clamp(green, 0.0f, 1.0f);
	this->blue = MathUtilities::Clamp(blue, 0.0f, 1.0f);
	this->alpha = MathUtilities::Clamp(alpha, 0.0f, 1.0f);
}

