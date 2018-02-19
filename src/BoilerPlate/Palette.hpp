#ifndef PALETTE_HPP_
#define PALETTE_HPP_

#include "Color.hpp"

class Palette
{
public:
	Palette();
	
	static const Color Amber;
	static const Color Black;
	static const Color Cyan;
	static const Color DarkNight;
	static const Color Red;

	static void SetBackground(Color color);
};

#endif /* PALETTE_HPP_ */

