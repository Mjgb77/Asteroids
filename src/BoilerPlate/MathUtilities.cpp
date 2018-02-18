#include "MathUtilities.hpp"
#include <intrin.h>
#include <cmath>
#include <ctime>

const float MathUtilities::PI = acosf(-1);

void randSeed() {
	static bool seeded = false;
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
}

int MathUtilities::nearestInt(float x) {
	return round(x);
}

int MathUtilities::nearestEven(float x) {
	int xLow = floor(x), xUp = ceil(x);
	if (xLow == xUp) return xUp + 1;
	return xLow & 1 ? xUp : xLow;
}

int MathUtilities::randInt(int max) {
	randSeed();
	return rand() % max;
}

float MathUtilities::randF() {
	randSeed();
	return float(rand()) / RAND_MAX;
}

float MathUtilities::toDeg(float rad) {
	return rad * 180 / PI;
}

float MathUtilities::toRad(float deg) {
	return deg * PI / 180;
}

float MathUtilities::calculateAngularDistanceInDeg(float startAngle, float endAngle) {
	float dis = endAngle - startAngle;
	return dis < 0 ? dis + 360 : dis;
}

float MathUtilities::calculateAngularDistanceInRad(float startAngle, float endAngle) {
	float dis = endAngle - startAngle;
	return dis < 0 ? dis + 2 * PI : dis;
}

bool MathUtilities::isPowerOfTwo(int x) {
	int bitCount = __popcnt(x);
	return bitCount == 1;
}

