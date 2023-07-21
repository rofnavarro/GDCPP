#include	"../include/engine.hpp"

Entity::Entity(size_t id, const std::string& tag)
	:m_id(id)
	,m_tag(tag)
	,m_alive(true)
{

}

bool	Entity::isActive() const
{
	return	(m_alive);
}

const std::string&	Entity::getTag() const
{
	return	(m_tag);
}

size_t	Entity::getId() const
{
	return	(m_id);
}

void	Entity::destroy()
{
	m_alive = false;
}
