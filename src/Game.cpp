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
			sLifespan();
			sSpawner();
			sMovement();
			sCollision();
		}
		sUserInput();
		sRender();

		m_currentFrame++;
	}
}

void	Game::init(const std::string& path)
{
	srand(time(0));

	std::ifstream	file(path);
	std::string		firstToken;

	if (!file.is_open())
	{
		std::cout << "Fail to open file:" << path << std::endl;
		exit (EXIT_FAILURE);
	}

	while (file.is_open() && file >> firstToken)
	{
		if (firstToken == "Window")
		{
			int	w = 0;
			int	h = 0;
			int frame = 0;
			int fullscreen = 0;

			file	>> w >> h >> frame >> fullscreen;
			if (fullscreen == 0)
			{
				m_window.create(sf::VideoMode(w, h), "GAME ENGINE v0.2", sf::Style::Close);
				m_window.setFramerateLimit(frame);
			}
			else if (fullscreen == 1)
			{
				auto fullscreenMode {sf::VideoMode::getFullscreenModes()};

				m_window.create(fullscreenMode[0], "GAME ENGINE v0.2", sf::Style::Close);
				m_window.setFramerateLimit(frame);
			}
		}
		else if (firstToken == "Font")
		{
			std::string				fontFile {};
			sf::Vector3<sf::Uint16>	RGB{};
			int						fontSize {};

			file	>> fontFile >> fontSize >> RGB.x >> RGB.y >> RGB.z;
			if (!m_font.loadFromFile(fontFile))
			{
				std::cerr << "Failed to load font. Filepath: " << fontFile;
			}
			m_text.setFont(m_font);
			m_text.setCharacterSize(fontSize);
			m_text.setFillColor(sf::Color(RGB.x, RGB.y, RGB.z));
		}
		else if (firstToken == "Player")
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
	m_text.setPosition(0.0f, 0.0f);
	m_text.setString(std::to_string(m_score));
	
	spawnPlayer();
}

void	Game::setPaused(bool paused)
{
	m_paused = paused;
}

void	Game::sMovement()
{
	sf::Vector2f	playerVelocity {};

	if (m_player->cInput->up)
		playerVelocity.y -= m_playerConfig.S;
	if (m_player->cInput->left)
		playerVelocity.x -= m_playerConfig.S;
	if (m_player->cInput->down)
		playerVelocity.y += m_playerConfig.S;
	if (m_player->cInput->right)
		playerVelocity.x += m_playerConfig.S;
	for (auto e : m_entities.getEntities())
	{
		if (e->getTag() == "player")
			m_player->cTransform->pos += playerVelocity;
		else if (e->cTransform)
			e->cTransform->pos += e->cTransform->speed;
		e->cTransform->angle += 2.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
	}
}

void	Game::sUserInput()
{

	sf::Event	event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_running = false;
			break ;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				m_running = false;
			else if (event.key.code == sf::Keyboard::P)
				m_paused ? setPaused(false) : setPaused(true);
			else if (event.key.code == sf::Keyboard::W)
				m_player->cInput->up = true;
			else if (event.key.code == sf::Keyboard::A)
				m_player->cInput->left = true;
			else if (event.key.code == sf::Keyboard::S)
				m_player->cInput->down = true;
			else if (event.key.code == sf::Keyboard::D)
				m_player->cInput->right = true;
			break ;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::W)
				m_player->cInput->up = false;
			else if (event.key.code == sf::Keyboard::A)
				m_player->cInput->left = false;
			else if (event.key.code == sf::Keyboard::S)
				m_player->cInput->down = false;
			else if (event.key.code == sf::Keyboard::D)
				m_player->cInput->right = false;
			break ;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button = sf::Mouse::Left)
			{
				if (m_player->cInput->leftMouse == false)
					m_player->cInput->leftMouse = true;
			}
			if (event.mouseButton.button = sf::Mouse::Right)
			{
				if (m_player->cInput->rightMouse == false)
					m_player->cInput->rightMouse = true;
			}
			break ;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button = sf::Mouse::Left)
			{
				if (m_player->cInput->leftMouse == false)
					m_player->cInput->leftMouse = true;
			}
			break ;
		default:
			break ;
		}
	}
}

void	Game::sLifespan()
{
	for (auto e : m_entities.getEntities())
	{
		if (!e->cLifespan)
			continue ;
		if (e->cLifespan->remaining > 0)
			e->cLifespan->remaining--;
		if (e->isActive() && e->cLifespan->remaining > 0)
		{
			float	alpha_rand {static_cast<float>(e->cLifespan->remaining) / static_cast<float>(e->cLifespan->total)};

			auto 	fill {e->cShape->circle.getFillColor()};
			sf::Color newFill {fill.r, fill.g, fill.b, static_cast<sf::Uint8>(255 * alpha_rand)};
			e->cShape->circle.setFillColor(newFill);

			auto 	outline {e->cShape->circle.getFillColor()};
			sf::Color newOutline {outline.r, outline.g, outline.b, static_cast<sf::Uint8>(255 * alpha_rand)};
			e->cShape->circle.setFillColor(newOutline);
		}
		else if (e->cLifespan->remaining <= 0)
			e->destroy();
	}
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
	m_window.draw(m_text);
	m_window.display();
}

void	Game::sSpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI)
		spawnEnemy();
	if (m_player->cInput->leftMouse == true)
	{
		sf::Vector2f	mouseP {static_cast<double>(sf::Mouse::getPosition(m_window).x), \
								static_cast<double>(sf::Mouse::getPosition(m_window).x)};
		spawnBullets(m_player, mouseP);
		m_player->cInput->leftMouse == false;
	}
	if (m_player->cInput->rightMouse == true)
	{
		spawnSpecialWeapon(m_player);
		m_player->cInput->rightMouse == false;
	}
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
	entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
	m_player = entity;
}

void	Game::spawnEnemy()
{
	auto			entity = m_entities.addEntity("enemy");
	sf::Vector2f	pos {m_enemyConfig.SR + (rand() % ((m_window.getSize().x - m_enemyConfig.SR) - m_enemyConfig.SR + 1)), \
						 m_enemyConfig.SR + (rand() % ((m_window.getSize().y - m_enemyConfig.SR) - m_enemyConfig.SR + 1))};
	sf::Vector2f	speed {m_enemyConfig.SMIN + (rand() % (int) (m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1)), \
						  m_enemyConfig.SMIN + (rand() % (int) (m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1))};
	int				vert = m_enemyConfig.VMIN + (rand() % (m_enemyConfig.VMAX + m_enemyConfig.VMIN + 1));
	sf::Color		fill {static_cast<sf::Uint8>(rand() % (256)), static_cast<sf::Uint8>(rand() % (256)), static_cast<sf::Uint8>(rand() % (256))};
	sf::Color		outline {static_cast<sf::Uint8>(m_enemyConfig.OR), static_cast<sf::Uint8>(m_enemyConfig.OG), static_cast<sf::Uint8>(m_enemyConfig.OB)};

	entity->cTransform = std::make_shared<CTransform>(pos, speed, 0.0f);
	entity->cScore = std::make_shared<CScore>(100);
	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vert, sf::Color(0, 0, 0), \
												sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), \
												m_enemyConfig.OT);
	entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
	
	m_lastEnemySpawnTime = m_currentFrame;
}

void	Game::spawnSmallEnemys(std::shared_ptr<Entity> e)
{
	size_t			vert {e->cShape->circle.getPointCount()};
	sf::Vector2f	position {e->cTransform->pos.x, e->cTransform->pos.x};
	double			p {(double)(std::sqrt((position.x * position.x) + (position.y * position.y)))};
	
	std::cout << "(" << position.x << ", " << position.y << ")" << std::endl;

	position.x = position.x / p;
	position.y = position.y / p;

	std::cout << "(" << position.x << ", " << position.y << ")" << std::endl;

	sf::Color		eFill {e->cShape->circle.getFillColor()};
	sf::Color		eOutline {e->cShape->circle.getOutlineColor()};
	float			eThick {e->cShape->circle.getOutlineThickness()};

	float			smallRad {e->cShape->circle.getRadius() * 0.5f};
	float			smallCollRad {e->cCollision->raidus * 0.5f};


	for (size_t i = 0; i < vert; ++i)
	{
		auto			ent = m_entities.addEntity("smallenemy");
		float			alpha {0};
		const double	pi {3.14159265359};
		double			rad {0};

		ent->cScore = std::make_shared<CScore>(e->cScore->score * 2);
		ent->cShape = std::make_shared<CShape>(smallRad, vert, eFill, eOutline, eThick);
		ent->cCollision = std::make_shared<CCollision>(smallCollRad);
		ent->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
	
		rad = (alpha * pi / 180.0);
		sf::Vector2f	velo {std::cos(rad) * position.x + std::sin(rad) * position.y, \
								std::cos(rad) * position.x - std::sin(rad) * position.y};
		float			l {(double)(std::sqrt((velo.x * velo.x) + (velo.y * velo.y)))};
		
		velo.x = velo.x / l;
		velo.y = velo.y / l;

		ent->cTransform = std::make_shared<CTransform>(e->cTransform->pos, velo, 0);

		alpha += 360 / vert;
	}
}

void	Game::spawnBullets(std::shared_ptr<Entity> entity, const sf::Vector2f& mousePos)
{
	auto 			bullet = m_entities.addEntity("bullet");
	sf::Vector2f	diff {mousePos.x - entity->cTransform->pos.x, mousePos.y - entity->cTransform->pos.y};
	sf::Vector2f	bulletVelocity (m_bulletConfig.S * diff.x, m_bulletConfig.S * diff.y);

	bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, bulletVelocity, 0);
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, \
											  sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), \
											  sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), \
											  m_bulletConfig.OT);
	bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
	bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
}

void	Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{

}
