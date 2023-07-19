#pragma	once

#include	"engine.hpp"

struct PlayerConfig
{
	int	SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;
};

struct EnemyConfig
{
	int	SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;
};

struct BulletConfig
{
	int	SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;
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
	int							m_score = 0;
	int							m_currentFrame = 0;
	int							m_lastEnemySpawnTime = 0;
	bool						m_paused = false;
	bool						m_running = true;

	std::shared_ptr<Entity>		m_player;

	void	init(const std::string& config);
	void	setPaused(bool paused);

	void	sMovement();
	void	sUserInput();
	void	sLifespan();
	void	sRender();
	void	sEnemySpawner();
	void	sCollision();

	void	spawnPlayer();

	void	spawnEnemy();
	void	spawnSmallEnemys(std::shared_ptr<Entity> entity);

	void	spawnBullets(std::shared_ptr<Entity> entity, const sf::Vector2f& mousePos);
	void	spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

};