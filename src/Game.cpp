#include	"../include/engine.hpp"

Game::Game(const std::string& config)
{
	init(config);	
}

void	Game::run()
{
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		
			m_currentFrame++;
		}
		sRender();

	}
}

void	Game::init(const std::string& path)
{
	std::ifstream	file(path);
	std::string		firstToken;

	while (file.is_open() && file >> firstToken)
	{
		if (firstToken == "Player")
		{
			file	>> m_playerConfig.SR \
					>> m_playerConfig.CR \
					>> m_playerConfig.FR \
					>> m_playerConfig.FG \
					>> m_playerConfig.FB \
					>> m_playerConfig.OR \
					>> m_playerConfig.OB \
					>> m_playerConfig.OT \
					>> m_playerConfig.V \
					>> m_playerConfig.S;
		}
		else if (firstToken == "Enemy")
		{
			file	>> m_enemyConfig.SR \
					>> m_enemyConfig.CR \
					>> m_enemyConfig.OR \
					>> m_enemyConfig.OG \
					>> m_enemyConfig.OB \
					>> m_enemyConfig.OT \
					>> m_enemyConfig.VMIN \
					>> m_enemyConfig.VMAX \
					>> m_enemyConfig.L \
					>> m_enemyConfig.SI \
					>> m_enemyConfig.SMIN \
					>> m_enemyConfig.SMAX;
		}
		else if (firstToken == "Bullet")
		{
			file	>> m_bulletConfig.SR \
					>> m_bulletConfig.CR \
					>> m_bulletConfig.FR \
					>> m_bulletConfig.FG \
					>> m_bulletConfig.FB \
					>> m_bulletConfig.OR \
					>> m_bulletConfig.OG \
					>> m_bulletConfig.OB \
					>> m_bulletConfig.OT \
					>> m_bulletConfig.V \
					>> m_bulletConfig.L \
					>> m_bulletConfig.S;
		}
	}
	file.close();

	m_window.create(sf::VideoMode(1280, 720), "GAME ENGINE - TEST GAME v.1");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void	Game::setPaused(bool paused)
{
	m_paused = paused;
}

void	Game::sMovement()
{
	m_player->cTransform->speed = {0.0f, 0.0f};
	if (m_player->cInput->up)
		m_player->cTransform->speed.y = -5;
	if (m_player->cInput->left)
		m_player->cTransform->speed.x = -5;
	if (m_player->cInput->down)
		m_player->cTransform->speed.y = 5;
	if (m_player->cInput->right)
		m_player->cTransform->speed.x = 5;

	m_player->cTransform->pos.x += m_player->cTransform->speed.x;
	m_player->cTransform->pos.y += m_player->cTransform->speed.y;

	for (auto e : m_entities.getEntities())
	{
		e->cTransform->speed.x = m_enemyConfig.SMIN + (rand() % ((int) m_enemyConfig.SMAX + 1));
		e->cTransform->speed.y = m_enemyConfig.SMIN + (rand() % ((int) m_enemyConfig.SMAX + 1));

		e->cTransform->pos.x += e->cTransform->speed.x;
		e->cTransform->pos.y += e->cTransform->speed.y;
	}
}

void	Game::sUserInput()
{

	sf::Event	event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_player->cInput->shoot = true;
				spawnBullets(m_player, sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				m_player->cInput->shoot = true;
				spawnSpecialWeapon(m_player);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
			m_player->cInput->shoot = false;
	}
}

void	Game::sLifespan()
{

}

void	Game::sRender()
{
	m_window.clear();
	for (auto e : m_entities.getEntities())
	{
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
		e->cShape->circle.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->circle);
	}
	m_window.display();
}

void	Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI)
		spawnEnemy();
}

void	Game::sCollision()
{

}

void	Game::spawnPlayer()
{
	auto	entity = m_entities.addEntity("player");
	float	px = (m_window.getSize().x / 2.0f);
	float	py = (m_window.getSize().y / 2.0f);

	entity->cTransform = std::make_shared<CTransform>(sf::Vector2f(px, py), sf::Vector2f(0.0f, 0.0f), 0.0f);
	entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, \
												sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), \
												sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), \
												m_playerConfig.OT);
	entity->cInput = std::make_shared<CInput>();
	m_player = entity;
}

void	Game::spawnEnemy()
{
	srand((unsigned) time(NULL));
	
	auto	entity = m_entities.addEntity("enemy");
	float	ex = m_enemyConfig.SR + (rand() % ((m_window.getSize().x - m_enemyConfig.SR) + 1));
	float	ey = m_enemyConfig.SR + (rand() % ((m_window.getSize().y - m_enemyConfig.SR) + 1));
	float	espeedx = m_enemyConfig.SMIN + (rand() % (int) m_enemyConfig.SMAX);
	float	espeedy = m_enemyConfig.SMIN + (rand() % (int) m_enemyConfig.SMAX);
	int		ev = m_enemyConfig.VMIN + (rand() % m_enemyConfig.VMAX);

	entity->cTransform = std::make_shared<CTransform>(sf::Vector2f(ex, ey), sf::Vector2f(espeedx, espeedy), 0.0f);
	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, ev, sf::Color(0, 0, 0), \
												sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), \
												m_enemyConfig.OT);
	
	m_lastEnemySpawnTime = m_currentFrame;
}

void	Game::spawnSmallEnemys(std::shared_ptr<Entity> e)
{
}

void	Game::spawnBullets(std::shared_ptr<Entity> entity, const sf::Vector2f& mousePos)
{
	auto bullet = m_entities.addEntity("bullet");

	bullet->cTransform = std::make_shared<CTransform>(mousePos, sf::Vector2f(0.0f, 0.0f), 0);
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, \
											  sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), \
											  sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), \
											  m_bulletConfig.OT);
}

void	Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{

}
