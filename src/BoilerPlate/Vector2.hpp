#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

struct Vector2 {

	float x, y;
	float length;

	Vector2();
	Vector2(float);
	Vector2(float, float);

	static Vector2 Origin;


	void Normalize();
	float SquaredLength() const;
	float Length() const;

	Vector2 operator+ (const Vector2&) const;
	Vector2 operator- (const Vector2&) const;
	Vector2 operator* (const Vector2&) const;
	Vector2 operator/ (const Vector2&) const;

	Vector2& operator=  (const Vector2&);
	Vector2& operator+= (const Vector2&);
	Vector2& operator-= (const Vector2&);
	Vector2& operator*= (const Vector2&);
	Vector2& operator/= (const Vector2&);

	bool operator== (const Vector2&) const;
	bool operator!= (const Vector2&) const;

	friend Vector2 operator* (float, const Vector2&);
	friend Vector2 operator* (const Vector2&, float);
};


#endif /* VECTOR2_HPP_ */