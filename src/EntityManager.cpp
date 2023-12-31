#include	"../include/EntityManager.hpp"

EntityManager::EntityManager()
:m_totalEntities(0)
{
	return ;
}

void	EntityManager::update()
{
	for (auto& e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
	removeDeadEntities(m_entities);
	for (auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
	m_toAdd.clear();
}

std::shared_ptr<Entity>	EntityManager::addEntity(const std::string& tag)
{
	auto	e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	m_toAdd.push_back(e);
	return (e);
}

void	EntityManager::removeDeadEntities(EntityVec& vec)
{
	vec.erase(std::remove_if(vec.begin(), vec.end(), \
							[] (auto& entity) { return !entity->isActive();}),
							vec.end());
}

const EntityVec&	EntityManager::getEntities()
{
	return (m_entities);
}

const EntityVec&	EntityManager::getEntities(const std::string& m_tag)
{
	return (m_entityMap[m_tag]);
}

