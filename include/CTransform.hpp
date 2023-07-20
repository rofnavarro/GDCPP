#pragma	once

#include	"engine.hpp"

class	CTransform
{
public:
	sf::Vector2f	pos = {0, 0};
	sf::Vector2f	speed = {0, 0};
	double			angle = {0};

	CTransform();
	CTransform(const sf::Vector2f & p, const sf::Vector2f & s, float a);

};
