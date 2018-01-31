#ifndef COLOR_H_
#define COLOR_H_

class Color
{

public:
	//Values should be in the range [0.0, 1.0], otherwise they will be clamped. By default they are 0.0
	double red, green, blue, alpha;
	
	Color(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 0.0);
	
};

#endif /* COLOR_H_ */