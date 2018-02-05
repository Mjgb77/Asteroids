#ifndef VECTOR3_H_
#define VECTOR3_H_

struct Vector2;

struct Vector3 {

	double x, y, z;
	double length;

	Vector3();
	Vector3(double);
	Vector3(const Vector2&);
	Vector3(double, double, double);

	static Vector3 Origin;


	void Normalize();
	double SquaredLength() const;
	double Length() const;

	Vector3 operator+ (const Vector3&) const;
	Vector3 operator- (const Vector3&) const;
	Vector3 operator* (const Vector3&) const;
	Vector3 operator/ (const Vector3&) const;

	Vector3& operator=  (const Vector3&);
	Vector3& operator+= (const Vector3&);
	Vector3& operator-= (const Vector3&);
	Vector3& operator*= (const Vector3&);
	Vector3& operator/= (const Vector3&);

	bool operator== (const Vector3&) const;
	bool operator!= (const Vector3&) const;

	friend Vector3 operator* (double, const Vector3&);
	friend Vector3 operator* (const Vector3&, double);

};

#endif /* VECTOR3_H_ */