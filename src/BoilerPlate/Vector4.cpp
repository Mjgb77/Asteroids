#include "Vector4.h"

#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

using namespace std;

Vector4 Vector4::Origin = Vector4();

Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f), length(0.0f) { }

Vector4::Vector4(float _uniform) : x(_uniform), y(_uniform), z(_uniform), w(_uniform) {
	length = Length();
}

Vector4::Vector4(const Vector2& V) : x(V.x), y(V.y), z (0.0f), w (0.0f) {
	length = Length();
}

Vector4::Vector4(const Vector3& V) : x(V.x), y(V.y), z(V.z), w(0.0f) {
	length = Length();
}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
	length = Length();
}

void Vector4::Normalize() {
	length = Length();

	float invLen = 1.0f / length;
	x *= invLen;
	y *= invLen;
	z *= invLen;
	w *= invLen;
	length = 1.0f;

}

float Vector4::SquaredLength() const {
	return x * x + y * y + z * z + w * w;
}

float Vector4::Length() const {
	return sqrt(SquaredLength());
}

Vector4& Vector4::operator= (const Vector4& rhs) {

	if (this != &rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}
	return *this;
}

Vector4& Vector4::operator+= (const Vector4& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;

	return *this;
}

Vector4& Vector4::operator-= (const Vector4& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;

	return *this;
}

Vector4& Vector4::operator*= (const Vector4& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;

	return *this;
}

Vector4& Vector4::operator/= (const Vector4& rhs) {
	if (rhs.x == 0 || rhs.y == 0 || rhs.z == 0 || rhs.w == 0) throw "Division by zero is not defined!";

	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	w /= rhs.w;

	return *this;
}


Vector4 Vector4::operator+(const Vector4& V) const {
	return Vector4(x + V.x, y + V.y, z + V.z, w + V.w);
}

Vector4 Vector4::operator-(const Vector4& V) const {
	return Vector4(x - V.x, y - V.y, z - V.z, w - V.w);
}

Vector4 Vector4::operator*(const Vector4& V) const {
	return Vector4(x * V.x, y * V.y, z * V.z, w * V.w);
}

Vector4 Vector4::operator/(const Vector4& V) const {
	if (V.x == 0 || V.y == 0 || V.z == 0 || V.w == 0) throw "Division by zero is not defined!";

	return Vector4(x / V.x, y / V.y, z / V.z, w / V.w);
}

bool Vector4::operator==(const Vector4& rhs) const {
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

bool Vector4::operator!=(const Vector4& rhs) const {
	return !(*this == rhs);
}

Vector4 operator*(float scale, const Vector4& rhs) {
	return Vector4(scale * rhs.x, scale * rhs.y, scale * rhs.z,  scale * rhs.w);
}

Vector4 operator*(const Vector4& lhs, float scale) {
	return Vector4(scale * lhs.x, scale * lhs.y, scale * lhs.z, scale * lhs.w);
}
