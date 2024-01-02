#include	"../include/Entity.hpp"

Entity::Entity(size_t id, const std::string& tag)
:m_id(id) ,m_tag(tag) ,m_alive(true)
{
	return ;
}

Entity::~Entity(void)
{
	return ;
}

bool	Entity::isActive() const
{
	return	(this->m_alive);
}

const std::string	&Entity::getTag() const
{
	return	(this->m_tag);
}

const size_t	&Entity::getId() const
{
	return	(this->m_id);
}

void	Entity::destroy()
{
	this->m_alive = false;
	return ;
}
