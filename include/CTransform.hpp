#pragma	once

#include	"engine.hpp"

class	CTransform
{
public:
	sf::Vector2f	pos {0.0f, 0.0f};
	sf::Vector2f	speed {0.0f, 0.0f};
	float			angle {0};

	CTransform(const sf::Vector2f & p, const sf::Vector2f & s, float a);

};
