#include "Vector2.h"
#include <cmath>

using namespace std;

Vector2 Vector2::Origin = Vector2();

Vector2::Vector2(): x(0.0), y(0.0), length(0.0) { }

Vector2::Vector2(double x, double y): x(x), y(y) {
	length = Length();
}

Vector2::Vector2(double _uniform): x(_uniform), y(_uniform) {
	length = Length();
}

void Vector2::Normalize() {
	length = Length();
	double invLen = 1.0 / length;
	x *= invLen;
	y *= invLen;
	length = 1.0;

}

double Vector2::SquaredLength() const {
	return x * x + y * y;
}

double Vector2::Length() const {
	return sqrt(SquaredLength());
}

Vector2& Vector2::operator= (const Vector2& rhs) {

	if (this != &rhs) {
		x = rhs.x;
		y = rhs.y;
	}
	return *this;
}

Vector2& Vector2::operator+= (const Vector2& rhs) {
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vector2& Vector2::operator-= (const Vector2& rhs) {
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Vector2& Vector2::operator*= (const Vector2& rhs) {
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

Vector2& Vector2::operator/= (const Vector2& rhs) {
	if (rhs.x == 0 || rhs.y == 0) throw "Division by zero is not defined!";

	x /= rhs.x;
	y /= rhs.y;

	return *this;
}


Vector2 Vector2::operator+(const Vector2& V) const {
	return Vector2(x + V.x, y + V.y);
}

Vector2 Vector2::operator-(const Vector2& V) const {
	return Vector2(x - V.x, y - V.y);
}

Vector2 Vector2::operator*(const Vector2& V) const {
	return Vector2(x * V.x, y * V.y);
}

Vector2 Vector2::operator/(const Vector2& V) const {
	if (V.x == 0 || V.y == 0) throw "Division by zero is not defined!";

	return Vector2(x/V.x, y/V.y);
}

bool Vector2::operator==(const Vector2& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2& rhs) const {
	return !(*this == rhs);
}

Vector2 operator*(double scale, const Vector2& rhs) {
	return Vector2(scale * rhs.x, scale * rhs.y);
}

Vector2 operator*(const Vector2& lhs, double scale) {
	return Vector2(scale * lhs.x, scale * lhs.y);
}
