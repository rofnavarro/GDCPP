#include	"../include/CShape.hpp"

CShape::CShape(float radius, int points, const sf::Color& fill, \
			const sf::Color& outline, float thickness)
:_circle(radius, points)
{
	_circle.setFillColor(fill);
	_circle.setOutlineColor(outline);
	_circle.setOutlineThickness(thickness);
	_circle.setOrigin(radius, radius);
	return ;
}

CShape::~CShape(void)
{
	return ;
}
