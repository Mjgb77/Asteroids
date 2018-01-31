#include "Color.h"
#include "MathUtilities.h"

Color::Color (double red, double green, double blue, double alpha) {
	this->red = MathUtilities::clamp(red, 0.0, 1.0);
	this->green = MathUtilities::clamp(green, 0.0, 1.0);
	this->blue = MathUtilities::clamp(blue, 0.0, 1.0);
	this->alpha = MathUtilities::clamp(alpha, 0.0, 1.0);
}

