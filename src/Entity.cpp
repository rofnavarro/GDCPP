#include	"../include/engine.hpp"

Entity::Entity(const std::string& tag, size_t id)
	:m_id(id)
	,m_tag(tag)
{

}

const std::string&	Entity::getTag()
{
	return	(m_tag);
}
