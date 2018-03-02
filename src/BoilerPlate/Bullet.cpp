#include "Bullet.hpp"

#include "DrawingTool.hpp"
#include "Palette.hpp"
 #include "MathUtilities.hpp"

#include <vector>

const int MAX_LIFE_TIME = 30;

/*CONSTRUCTOR*/
std::vector <Vector2> bulletPoints;

void InitializeBulletPoints() {
	bulletPoints.push_back({ -2.0f, 2.0f });
	bulletPoints.push_back({ 2.0f, 2.0f });
	bulletPoints.push_back({ 2.0f, -2.0f });
	bulletPoints.push_back({ -2.0f, -2.0f });
}

Bullet::Bullet(Game* parent)
	: SpaceObject(parent) {
	m_lifeTime = 0;
	m_mass = 0.01f;
	m_radius = 3.0f;
	
	InitializeBulletPoints();
}

/*PUBLIC FUNCTIONS*/
bool Bullet::IsLifeTimeOver() {
	return m_lifeTime > MAX_LIFE_TIME;
}

void Bullet::Update(float deltaTime) {
	SpaceObject::Update(deltaTime);
	m_lifeTime++;
}

void Bullet::Render() {
	
	DrawingTool::DrawPolygon(bulletPoints, m_position, Palette::White, MathUtilities::ToDeg(m_rotAng));

}
