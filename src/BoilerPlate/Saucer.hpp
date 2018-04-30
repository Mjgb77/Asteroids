#ifndef SAUCER_HPP_
#define SAUCER_HPP_

#include "SpaceObject.hpp"
#include "Bullet.hpp"

//struct SaucerSize {
//	enum Size { SMALL, BIG };
//	Si
//	int getScore() {
//
//	}
//};

class Saucer : public SpaceObject
{
public:
	/*CONSTRUCTOR*/
	Saucer(Game *);

	/*PUBLIC FUNCTIONS*/

	bool IsReadyToShot();
	bool IsAlive();
	void Update(float);
	void Render() override;

	void Kill();
	Bullet * Shot();

private:
	int m_charge;
	int m_horizontalDirection; //0 for Left , 1 for Right
	bool m_isAlive;
};

#endif /* SAUCER_HPP_ */

