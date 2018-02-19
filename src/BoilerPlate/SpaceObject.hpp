#ifndef SPACEOBJECT_HPP_
#define SPACEOBJECT_HPP_

#include "Vector2.hpp"

class SpaceObject
{
protected:
	int m_width, m_height;
	float m_mass;
	float m_rotAng;
	Vector2 * position;
	void WarpPosition();
public:
	SpaceObject (int, int);

	void UpdateSize(int, int);

	virtual void Update () = 0;
	virtual void Render () = 0;
};

#endif // !SPACEOBJECT_HPP_

