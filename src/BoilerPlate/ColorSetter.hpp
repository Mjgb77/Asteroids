#ifndef COLORSETTER_HPP_
#define COLORSETTER_HPP_

#include "Color.hpp"

class ColorSetter
{
public:
	ColorSetter();
	
	static const Color Amber;
	static const Color Black;
	static const Color Cyan;
	static const Color DarkNight;
	static const Color Red;

	static void setBackground(Color color);
};

#endif /* COLORSETTER_HPP_ */

