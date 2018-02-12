#ifndef VECTOR3_H_
#define VECTOR3_H_

struct Vector2;

struct Vector3 {

	float x, y, z;
	float length;

	Vector3();
	Vector3(float);
	Vector3(const Vector2&);
	Vector3(float, float, float);

	static Vector3 Origin;


	void Normalize();
	float SquaredLength() const;
	float Length() const;

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

	friend Vector3 operator* (float, const Vector3&);
	friend Vector3 operator* (const Vector3&, float);

};

#endif /* VECTOR3_H_ */
