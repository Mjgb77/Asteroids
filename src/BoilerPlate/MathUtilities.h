#ifndef MATHUTILITIES_H_
#define MATHUTILITIES_H_

#include <algorithm>
using namespace std;

class MathUtilities {

public:
	static int nearestInt (double x);
	static int nearestEven (double x); //Return the nearest even integer, if there is a tie return the greatest

	static double toDeg (double rad);
	static double toRad (double deg);

	static double calculateAngularDistanceInDeg (double startAngle, double endAngle);
	static double calculateAngularDistanceInRad (double startAngle, double endAngle);

	static bool isPowerOfTwo (int x);

	template <typename T>
	static T getMax(T x) { return x; }

	template<typename T, typename... Args>
	static T getMax(T x, Args... args) {
		return max(x, getMax(args...));
	}

	template <typename T>
	static T getMin(T x) { return x; }

	template<typename T, typename... Args>
	static T getMin(T x, Args ... args) {
		return min(x, getMin(args...));
	}

	template <typename T>
	static T clamp(T x, T startValue, T endValue) {
		return min(max(startValue, x), endValue);
	}

	//esa es la de clamp

	template <typename T>
	static T interpolate(T startValue, T endValue, double fraction) {
		return startValue + round((endValue - startValue)*fraction);
	}
};

#endif /* MATHUTILITIES_H_ */
