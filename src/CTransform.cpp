#include	"../include/CTransform.hpp"

CTransform::CTransform(const sf::Vector2f & p, const sf::Vector2f & s, float a)
:_pos(p) ,_speed(s) ,_angle(a)
{
	return ;
}

CTransform::~CTransform(void)
{
	return ;
}

const sf::Vector2f	&CTransform::getPos(void) const
{
	return (this->_pos);
}

const sf::Vector2f	&CTransform::getSpeed(void) const
{
	return (this->_speed);
}

const float	&CTransform::getAngle(void) const
{
	return (this->_angle);
}

void	CTransform::setPos(sf::Vector2f newPos)
{
	this->_pos = newPos;
	return ;
}

void	CTransform::setSpeed(sf::Vector2f newSpeed)
{
	this->_speed = newSpeed;
	return ;
}

void	CTransform::setAngle(float newAngle)
{
	this->_angle = newAngle;
	return ;
}
