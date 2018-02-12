#include "Color.h"
#include "MathUtilities.h"

Color::Color (float red, float green, float blue, float alpha) {
	this->red = MathUtilities::clamp(red, 0.0f, 1.0f);
	this->green = MathUtilities::clamp(green, 0.0f, 1.0f);
	this->blue = MathUtilities::clamp(blue, 0.0f, 1.0f);
	this->alpha = MathUtilities::clamp(alpha, 0.0f, 1.0f);
}

