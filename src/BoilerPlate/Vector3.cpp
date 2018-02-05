#include "Vector3.h"

#include "Vector2.h"
#include <cmath>

using namespace std;

Vector3 Vector3::Origin = Vector3();

Vector3::Vector3() : x(0.0), y(0.0), z(0.0), length(0.0) { }

Vector3::Vector3(double _uniform) : x(_uniform), y(_uniform), z(_uniform) {
	length = Length();
}

Vector3::Vector3(const Vector2& V) : x(V.x), y(V.y) {
	length = Length();
}

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {
	length = Length();
}

void Vector3::Normalize() {
	length = Length();
	
	double invLen = 1.0 / length;
	x *= invLen;
	y *= invLen;
	z *= invLen;
	length = 1.0;

}

double Vector3::SquaredLength() const {
	return x * x + y * y + z * z;
}

double Vector3::Length() const {
	return sqrt(SquaredLength());
}

Vector3& Vector3::operator= (const Vector3& rhs) {

	if (this != &rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}
	return *this;
}

Vector3& Vector3::operator+= (const Vector3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vector3& Vector3::operator-= (const Vector3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vector3& Vector3::operator*= (const Vector3& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

Vector3& Vector3::operator/= (const Vector3& rhs) {
	if (rhs.x == 0 || rhs.y == 0 || rhs.z == 0) throw "Division by zero is not defined!";

	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}


Vector3 Vector3::operator+(const Vector3& V) const {
	return Vector3(x + V.x, y + V.y, z + V.z);
}

Vector3 Vector3::operator-(const Vector3& V) const {
	return Vector3(x - V.x, y - V.y, z - V.z);
}

Vector3 Vector3::operator*(const Vector3& V) const {
	return Vector3(x * V.x, y * V.y, z * V.z);
}

Vector3 Vector3::operator/(const Vector3& V) const {
	if (V.x == 0 || V.y == 0 || V.z == 0) throw "Division by zero is not defined!";

	return Vector3(x / V.x, y / V.y, z / V.z);
}

bool Vector3::operator==(const Vector3& rhs) const {
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool Vector3::operator!=(const Vector3& rhs) const {
	return !(*this == rhs);
}

Vector3 operator*(double scale, const Vector3& rhs) {
	return Vector3(scale * rhs.x, scale * rhs.y, scale * rhs.z);
}

Vector3 operator*(const Vector3& lhs, double scale) {
	return Vector3(scale * lhs.x, scale * lhs.y, scale * lhs.z);
}
