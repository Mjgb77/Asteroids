#ifndef SPACEOBJECT_HPP_
#define SPACEOBJECT_HPP_

#include "Vector2.hpp"
#include "Color.hpp"
#include <vector>

class Game;

class SpaceObject
{

public:
	/*CONSTRUCTOR*/
	SpaceObject(Game *);

	/*PUBLIC FUNCTIONS*/
	std::vector<Vector2> GetPointsFrom(std::string);
	bool HasCollisionWith(SpaceObject *);

	void Update(float);
	virtual void Render() = 0;

	/*DEBUGGING MEMBERS AND FUNCTIONS*/
	Color m_circleColor;
	void DrawCircleAround();
	void DrawSegmentIfNearbyTo(SpaceObject *);

protected:
	/*PROTECTED MEMBERS*/
	Game * m_parent;
	
	float m_mass;
	float m_radius;
	float m_rotAng;
	
	Vector2 m_position, m_velocity;
	
	/*PROTECTED FUNCTIONS*/
	void WarpPosition();
};

#endif // !SPACEOBJECT_HPP_
