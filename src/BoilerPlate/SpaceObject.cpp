#include "SpaceObject.hpp"
#include "MathUtilities.hpp"

#include "Game.hpp"
#include "DrawingTool.hpp"
#include "Palette.hpp"

#include <fstream>

/*PUBLIC FUNCTIONS*/
SpaceObject::SpaceObject(Game * parent) : 
	m_parent(parent), m_mass(1.0f), m_rotAng(0.0f) {
}

std::vector<Vector2> SpaceObject::GetPointsFrom(std::string fileName)
{
	std::ifstream ifs(fileName);

	std::vector<Vector2> points;

	while (ifs.good()) {
		float x, y;
		ifs >> x >> y;
		points.push_back({ x, y });
	}

	ifs.close();

	return points;
}

bool SpaceObject::HasCollisionWith(SpaceObject * obj)
{
	float dis = (obj->m_position - m_position).SquaredLength();
	float radioSum = m_radius + obj->m_radius;
	return dis < radioSum*radioSum;
}

void SpaceObject::Update(float deltaTime) {
	static int count = 0;
	m_position += (m_velocity * deltaTime);

	WarpPosition();
}

/*DEBUGGING FUNCTIONS*/

const float NEARBY_DISTANCE = 300;

void SpaceObject::DrawCircleAround() {
	DrawingTool::DrawCircle(m_position, m_radius, m_circleColor, 3.0f);
}


void SpaceObject::DrawSegmentIfNearbyTo(SpaceObject * obj)
{
	float dis = (obj->m_position - m_position).SquaredLength();

	if (dis < NEARBY_DISTANCE * NEARBY_DISTANCE)
		DrawingTool::DrawSegment(m_position, obj->m_position, Palette::White, 3.0f);

}

/*PROTECTED FUNCTIONS*/
void SpaceObject::WarpPosition () {
	if (m_position.x > m_parent->m_maxX) m_position.x -= m_parent->m_width;
	if (m_position.y > m_parent->m_maxY) m_position.y -= m_parent->m_height;

	if (m_position.x < m_parent->m_minX) m_position.x += m_parent->m_width;
	if (m_position.y < m_parent->m_minY) m_position.y += m_parent->m_height;
}
