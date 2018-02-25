#ifndef MATHUTILITIES_HPP_
#define MATHUTILITIES_HPP_

#include <algorithm>

class MathUtilities {

public:
	static const float PI;

	static int NearestInt (float x);
	static int NearestEven (float x); //Return the nearest even integer, if there is a tie return the greatest

	static int RandInt (int);
	static float RandFloat(); //Return a random float from 0.0 to 1.0

	static float ToDeg (float rad);
	static float ToRad (float deg);

	static float CalculateAngularDistanceInDeg (float startAngle, float endAngle);
	static float CalculateAngularDistanceInRad (float startAngle, float endAngle);

	static bool IsPowerOfTwo (int x);

	template <typename T>
	static T GetMax(T x) { return x; }

	template<typename T, typename... Args>
	static T GetMax(T x, Args... args) {
		return std::max(x, getMax(args...));
	}

	template <typename T>
	static T GetMin(T x) { return x; }

	template<typename T, typename... Args>
	static T GetMin(T x, Args ... args) {
		return std::min(x, getMin(args...));
	}

	template <typename T>
	static T Clamp(T x, T startValue, T endValue) {
		return std::min(std::max(startValue, x), endValue);
	}

	template <typename T>
	static T Interpolate(T startValue, T endValue, float fraction) {
		return startValue + (endValue - startValue)*fraction;
	}
};

#endif /* MATHUTILITIES_H_ */
