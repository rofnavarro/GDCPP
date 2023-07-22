#pragma	once

#include	"engine.hpp"

struct PlayerConfig
{
	int		SR {};
	int		CR {};
	int		FR {};
	int		FG {};
	int		FB {};
	int		OR {};
	int		OG {};
	int		OB {};
	int		OT {};
	int		V {};
	float	S {};
};

struct EnemyConfig
{
	int		SR {};
	int		CR {};
	int		OR {};
	int		OG {};
	int		OB {};
	int		OT {};
	int		VMIN {};
	int		VMAX {};
	int		L {};
	int		SI {};
	float	SMIN {};
	float	SMAX {};
};

struct BulletConfig
{
	int		SR {};
	int		CR {};
	int		FR {};
	int		FG {};
	int		FB {};
	int		OR {};
	int		OG {};
	int		OB {};
	int		OT {};
	int		V {};
	int		L {};
	float	S {};
};

class Game
{
private:
	sf::RenderWindow			m_window;
	EntityManager				m_entities;
	sf::Font					m_font;
	sf::Text					m_text;
	PlayerConfig				m_playerConfig;
	EnemyConfig					m_enemyConfig;
	BulletConfig				m_bulletConfig;
	int							m_score {0};
	int							m_currentFrame {0};
	int							m_lastEnemySpawnTime {0};
	bool						m_paused {false};
	bool						m_running {true};

	std::shared_ptr<Entity>		m_player;

	void	init(const std::string& config);
	void	setPaused(bool paused);

	void	sMovement();
	void	sUserInput();
	void	sLifespan();
	void	sRender();
	void	sSpawner();
	void	sCollision();

	void	spawnPlayer();

	void	spawnEnemy();
	void	spawnSmallEnemys(std::shared_ptr<Entity> entity);

	void	spawnBullets(std::shared_ptr<Entity> entity, const sf::Vector2f& mousePos);
	void	spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
	Game(const std::string& config);

	void	run();

};
