#ifndef SPACEOBJECT_HPP_
#define SPACEOBJECT_HPP_

#include "Vector2.hpp"
#include "Color.hpp"

class SpaceObject
{

public:
	/*CONSTRUCTOR*/
	SpaceObject(int, int);

	/*PUBLIC FUNCTIONS*/
	void UpdateSize(int, int);

	bool HasCollisionWith(SpaceObject *);

	void Update(float);
	virtual void Render() = 0;

	/*DEBUGGING MEMBERS AND FUNCTIONS*/
	Color m_circleColor;
	void DrawCircleAround();
	void DrawSegmentIfNearbyTo(SpaceObject *);

protected:
	/*PROTECTED MEMBERS*/
	int m_width, m_height;
	
	float m_mass;
	float m_radius;
	float m_rotAng;
	
	Vector2 m_position, m_velocity;
	
	/*PROTECTED FUNCTIONS*/
	void WarpPosition();
};

#endif // !SPACEOBJECT_HPP_
