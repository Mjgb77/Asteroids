#include "Vector2.hpp"
#include <cmath>

Vector2 Vector2::Origin = Vector2();

Vector2::Vector2(): x(0.0f), y(0.0f), length(0.0f) { }

Vector2::Vector2(float x, float y): x(x), y(y) {
	length = Length();
}

Vector2::Vector2(float _uniform): x(_uniform), y(_uniform) {
	length = Length();
}

void Vector2::Normalize() {
	length = Length();
	float invLen = 1.0f / length;
	x *= invLen;
	y *= invLen;
	length = 1.0f;

}

float Vector2::SquaredLength() const {
	return x * x + y * y;
}

float Vector2::Length() const {
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

Vector2 operator*(float scale, const Vector2& rhs) {
	return Vector2(scale * rhs.x, scale * rhs.y);
}

Vector2 operator*(const Vector2& lhs, float scale) {
	return Vector2(scale * lhs.x, scale * lhs.y);
}
