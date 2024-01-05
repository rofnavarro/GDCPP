#include	"../include/CShape.hpp"

CShape::CShape(float radius, int points, const sf::Color& fill, \
			const sf::Color& outline, float thickness)
:_circle(radius, points)
{
	this->_circle.setFillColor(fill);
	this->_circle.setOutlineColor(outline);
	this->_circle.setOutlineThickness(thickness);
	this->_circle.setOrigin(radius, radius);
	return ;
}

CShape::~CShape(void)
{
	return ;
}

sf::CircleShape	&CShape::getCircle(void)
{
	return (this->_circle);
}
