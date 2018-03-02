#ifndef PALETTE_HPP_
#define PALETTE_HPP_

#include "Color.hpp"

class Palette
{
public:
	Palette();
	
	static const Color Amber;
	static const Color Cyan;
	static const Color DarkNight;
	static const Color Flame;
	static const Color Green;
	static const Color Red;
	static const Color White;

	static void SetBackground(Color color);
};

#endif /* PALETTE_HPP_ */

