#include	"../include/engine.hpp"

EntityManager::EntityManager()
{

}

std::shared_ptr<Entity>	EntityManager::addEntity(const std::string& tag)
{
	auto	e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
	m_toAdd.push_back(e);
	return (e);
}

void	EntityManager::update()
{
	for (auto e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
	for (auto e : m_entities)
	{
		// if ()
	}
	m_toAdd.clear();
}
