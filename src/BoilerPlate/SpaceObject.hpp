#ifndef SPACEOBJECT_HPP_
#define SPACEOBJECT_HPP_

#include "Vector2.hpp"

class SpaceObject
{
protected:
	int width, height;
	float mass;
	float rotAng;
	Vector2 * position;
	void WarpPos();
public:
	SpaceObject (int, int);

	void UpdateSize(int, int);

	virtual void Update () = 0;
	virtual void Render () = 0;
};

#endif // !SPACEOBJECT_HPP_

