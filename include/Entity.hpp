#pragma	once

#ifndef ENTITY_HPP
# define ENTITY_HPP

# include	"engine.hpp"

class	Entity
{
private:
	friend class	EntityManager;
	
	size_t							m_id {0};
	std::string						m_tag {"default"};
	bool							m_alive {true};

									Entity(size_t id, const std::string& tag);

public:
	std::shared_ptr<CTransform>		cTransform;
	std::shared_ptr<CShape>			cShape;
	std::shared_ptr<CCollision>		cCollision;
	std::shared_ptr<CInput>			cInput;
	std::shared_ptr<CScore>			cScore;
	std::shared_ptr<CLifespan>		cLifespan;

	bool							isActive() const;
	const std::string				&getTag() const;
	const size_t					&getId() const;
	void							destroy();

};

#endif