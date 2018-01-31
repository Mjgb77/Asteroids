#include "MathUtilities.h"
#include <intrin.h>
#include <cmath>
using namespace std;

const double PI = acos(-1);

int MathUtilities::nearestInt(double x) {
	return round(x);
}

int MathUtilities::nearestEven(double x) {
	int xLow = floor(x), xUp = ceil(x);
	if (xLow == xUp) return xUp + 1;
	return xLow & 1 ? xUp : xLow;
}

double MathUtilities::toDeg(double rad) {
	return rad * 180 / PI;
}

double MathUtilities::toRad(double deg) {
	return deg * PI / 180;
}

double MathUtilities::calculateAngularDistanceInDeg(double startAngle, double endAngle) {
	double dis = endAngle - startAngle;
	return dis < 0 ? dis + 360 : dis;
}

double MathUtilities::calculateAngularDistanceInRad(double startAngle, double endAngle) {
	double dis = endAngle - startAngle;
	return dis < 0 ? dis + 2 * PI : dis;
}

bool MathUtilities::isPowerOfTwo(int x) {
	int bitCount = __popcnt(x);
	return bitCount == 1;
}

