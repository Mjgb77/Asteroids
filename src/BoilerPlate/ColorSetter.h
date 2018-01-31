#ifndef COLORSETTER_H_
#define COLORSETTER_H_

#include "Color.h"

class ColorSetter
{
public:
	ColorSetter();
	
	static const Color Amber;
	static const Color Black;
	static const Color Cyan;
	static const Color Navy;
	static const Color Red;

	static void setBackground(Color color);
};

#endif /* COLORSETTER_H_ */

