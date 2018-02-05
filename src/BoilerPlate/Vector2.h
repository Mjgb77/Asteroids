#ifndef VECTOR2_H_
#define VECTOR2_H_

struct Vector2 {

	double x, y;
	double length;

	Vector2();
	Vector2(double);
	Vector2(double, double);

	static Vector2 Origin;


	void Normalize();
	double SquaredLength() const;
	double Length() const;

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

	friend Vector2 operator* (double, const Vector2&);
	friend Vector2 operator* (const Vector2&, double);
};


#endif /* VECTOR2_H_ */