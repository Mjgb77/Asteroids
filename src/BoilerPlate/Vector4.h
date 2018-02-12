#ifndef VECTOR4_H_
#define VECTOR4_H_

struct Vector2;
struct Vector3;

struct Vector4 {

	float x, y, z, w;
	float length;

	Vector4();
	Vector4(float);
	Vector4(const Vector2&);
	Vector4(const Vector3&);
	Vector4(float, float, float, float);

	static Vector4 Origin;


	void Normalize();
	float SquaredLength() const;
	float Length() const;

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

	friend Vector4 operator* (float, const Vector4&);
	friend Vector4 operator* (const Vector4&, float);

};

#endif /* VECTOR4_H_ */
