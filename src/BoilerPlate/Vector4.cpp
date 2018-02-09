#include "Vector4.h"

#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

using namespace std;

Vector4 Vector4::Origin = Vector4();

Vector4::Vector4() : x(0.0), y(0.0), z(0.0), w(0.0), length(0.0) { }

Vector4::Vector4(double _uniform) : x(_uniform), y(_uniform), z(_uniform), w(_uniform) {
	length = Length();
}

Vector4::Vector4(const Vector2& V) : x(V.x), y(V.y) {
	z = w = 0.0;
	length = Length();
}

Vector4::Vector4(const Vector3& V) : x(V.x), y(V.y), z(V.z) {
	w = 0.0;
	length = Length();
}

Vector4::Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {
	length = Length();
}

void Vector4::Normalize() {
	length = Length();

	double invLen = 1.0 / length;
	x *= invLen;
	y *= invLen;
	z *= invLen;
	w *= invLen;
	length = 1.0;

}

double Vector4::SquaredLength() const {
	return x * x + y * y + z * z + w * w;
}

double Vector4::Length() const {
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

Vector4 operator*(double scale, const Vector4& rhs) {
	return Vector4(scale * rhs.x, scale * rhs.y, scale * rhs.z,  scale * rhs.w);
}

Vector4 operator*(const Vector4& lhs, double scale) {
	return Vector4(scale * lhs.x, scale * lhs.y, scale * lhs.z, scale * lhs.w);
}
