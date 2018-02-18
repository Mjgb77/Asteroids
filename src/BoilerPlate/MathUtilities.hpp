#ifndef MATHUTILITIES_HPP_
#define MATHUTILITIES_HPP_

#include <algorithm>

class MathUtilities {

public:
	static const float PI;

	static int nearestInt (float x);
	static int nearestEven (float x); //Return the nearest even integer, if there is a tie return the greatest

	static int randInt (int);
	static float randF();

	static float toDeg (float rad);
	static float toRad (float deg);

	static float calculateAngularDistanceInDeg (float startAngle, float endAngle);
	static float calculateAngularDistanceInRad (float startAngle, float endAngle);

	static bool isPowerOfTwo (int x);

	template <typename T>
	static T getMax(T x) { return x; }

	template<typename T, typename... Args>
	static T getMax(T x, Args... args) {
		return std::max(x, getMax(args...));
	}

	template <typename T>
	static T getMin(T x) { return x; }

	template<typename T, typename... Args>
	static T getMin(T x, Args ... args) {
		return std::min(x, getMin(args...));
	}

	template <typename T>
	static T clamp(T x, T startValue, T endValue) {
		return std::min(std::max(startValue, x), endValue);
	}

	template <typename T>
	static T interpolate(T startValue, T endValue, float fraction) {
		return startValue + (endValue - startValue)*fraction;
	}
};

#endif /* MATHUTILITIES_H_ */
