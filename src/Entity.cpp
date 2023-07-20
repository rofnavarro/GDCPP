#include	"../include/engine.hpp"

Entity::Entity(size_t id, const std::string& tag)
	:m_id(id)
	,m_tag(tag)
{

}

bool	Entity::isActive() const
{
	return	(m_alive);
}

const std::string&	Entity::getTag() const
{
	return	((const std::string) m_tag);
}

const size_t	Entity::getId() const
{
	return	((const size_t) m_id);
}

void	Entity::destroy()
{

}
