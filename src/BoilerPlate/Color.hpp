#ifndef COLOR_HPP_
#define COLOR_HPP_

struct Color
{

	//Values should be in the range [0.0, 1.0], otherwise they will be clamped. By default they are 0.0
	float red, green, blue, alpha;
	
	Color(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 0.0f);
	
};

#endif /* COLOR_HPP_ */
