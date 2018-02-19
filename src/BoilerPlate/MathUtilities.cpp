#include "MathUtilities.hpp"
#include <intrin.h>
#include <cmath>
#include <ctime>

const float MathUtilities::PI = acosf(-1);

void RandSeed() {
	static bool seeded = false;
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
}

int MathUtilities::NearestInt(float x) {
	return round(x);
}

int MathUtilities::NearestEven(float x) {
	int xLow = floor(x), xUp = ceil(x);
	if (xLow == xUp) return xUp + 1;
	return xLow & 1 ? xUp : xLow;
}

int MathUtilities::RandInt(int max) {
	RandSeed();
	return rand() % max;
}

float MathUtilities::RandFloat() {
	RandSeed();
	return float(rand()) / RAND_MAX;
}

float MathUtilities::ToDeg(float rad) {
	return rad * 180 / PI;
}

float MathUtilities::ToRad(float deg) {
	return deg * PI / 180;
}

float MathUtilities::CalculateAngularDistanceInDeg(float startAngle, float endAngle) {
	float dis = endAngle - startAngle;
	return dis < 0 ? dis + 360 : dis;
}

float MathUtilities::CalculateAngularDistanceInRad(float startAngle, float endAngle) {
	float dis = endAngle - startAngle;
	return dis < 0 ? dis + 2 * PI : dis;
}

bool MathUtilities::IsPowerOfTwo(int x) {
	int bitCount = __popcnt(x);
	return bitCount == 1;
}

