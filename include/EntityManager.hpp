#pragma	once

#include	"engine.hpp"

typedef	std::vector	<std::shared_ptr<Entity>>	EntityVec;
typedef	std::map	<std::string, EntityVec>	EntityMap;

class	EntityManager
{
private:
	EntityVec	m_entities;
	EntityVec	m_toAdd;
	EntityMap	m_entityMap;
	size_t		m_totalEntities = {0};
	
	void		removeDeadEntities(EntityVec& vec);

public:
								EntityManager();
	void						update();
	std::shared_ptr<Entity>		addEntity(const std::string& m_tag);
	const EntityVec&			getEntities();
	const EntityVec&			getEntities(const std::string& m_tag);

};
