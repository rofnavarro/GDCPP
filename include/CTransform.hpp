#include	"engine.hpp"

class	CTransform
{
public:
	sf::Vector2i	pos = {0, 0};
	sf::Vector2f	velocity = {0, 0};

					CTransform();
					CTransform(const sf::Vector2i & p, const sf::Vector2f & v);
};
