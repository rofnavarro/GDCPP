#pragma	once

#ifndef CTRANSFORM_HPP
# define CTRANSFORM_HPP

# include	<SFML/Window.hpp>
# include	<SFML/Graphics.hpp>

class	CTransform
{
private:
	sf::Vector2f		_pos {0.0f, 0.0f};
	sf::Vector2f		_speed {0.0f, 0.0f};
	float				_angle {0};

public:
						CTransform(const sf::Vector2f & p, const sf::Vector2f & s, float a);
						~CTransform(void);

	const sf::Vector2f	&getPos(void) const;
	const sf::Vector2f	&getSpeed(void) const;
	const float			&getAngle(void) const;
	void				setPos(sf::Vector2f newPos);
	void				setSpeed(sf::Vector2f newSpeed);
	void				setAngle(float newAngle);

};

#endif