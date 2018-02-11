#ifndef VECTOR4_H_
#define VECTOR4_H_

struct Vector2;
struct Vector3;

struct Vector4 {

	double x, y, z, w;
	double length;

	Vector4();
	Vector4(double);
	Vector4(const Vector2&);
	Vector4(const Vector3&);
	Vector4(double, double, double, double);

	static Vector4 Origin;


	void Normalize();
	double SquaredLength() const;
	double Length() const;

	Vector4 operator+ (const Vector4&) const;
	Vector4 operator- (const Vector4&) const;
	Vector4 operator* (const Vector4&) const;
	Vector4 operator/ (const Vector4&) const;

	Vector4& operator=  (const Vector4&);
	Vector4& operator+= (const Vector4&);
	Vector4& operator-= (const Vector4&);
	Vector4& operator*= (const Vector4&);
	Vector4& operator/= (const Vector4&);

	bool operator== (const Vector4&) const;
	bool operator!= (const Vector4&) const;

	friend Vector4 operator* (double, const Vector4&);
	friend Vector4 operator* (const Vector4&, double);

};

#endif /* VECTOR4_H_ */
