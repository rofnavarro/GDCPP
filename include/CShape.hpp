#pragma	once

#ifndef CSHAPE_HPP
# define CSHAPE_HPP

# include	"engine.hpp"

class	CShape
{
private:
	sf::CircleShape	_circle;

public:
	CShape(float radius, int points, const sf::Color& fill, \
			const sf::Color& outline, float thickness);
	~CShape(void);

};

#endif