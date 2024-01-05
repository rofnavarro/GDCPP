#include	"../include/Game.hpp"

Game::Game(const std::string &config)
{
	this->init(config);
	return ;
}

Game::~Game(void)
{
	return ;
}

void	Game::run()
{
	while (this->m_running)
	{
 		this->m_entities.update();

		if (!this->m_paused)
		{
			this->sLifespan();
			this->sSpawner();
			this->sMovement();
			this->sCollision();
		}
		this->sUserInput();
		this->sRender();

		++this->m_currentFrame;
	}
}

void	Game::init(const std::string &path)
{
	srand(time(0));

	std::ifstream	file{path};
	std::string		firstToken;

	if (!file.is_open())
	{
		std::cerr << "Fail to open file:" << path << std::endl;
		exit(EXIT_FAILURE);
	}

	while (file.is_open() && file >> firstToken)
	{
		if (firstToken == "Window")
		{
			int	w = 0;
			int	h = 0;
			int frame = 0;
			int fullscreen = 0;

			file >> w >> h >> frame >> fullscreen;

			if (fullscreen == 0)
			{
				this->m_window.create(sf::VideoMode(w, h), "GAME ENGINE v0.2", sf::Style::Close);
				this->m_window.setFramerateLimit(frame);
			}
			else if (fullscreen == 1)
			{
				auto fullscreenMode {sf::VideoMode::getFullscreenModes()};

				this->m_window.create(fullscreenMode[0], "GAME ENGINE v0.2", sf::Style::Close);
				this->m_window.setFramerateLimit(frame);
			}
		}
		else if (firstToken == "Font")
		{
			int						fontSize {};
			std::string				fontFile {};
			sf::Vector3<sf::Uint16>	RGB{};

			file >> fontFile;
			
			if (!this->m_font.loadFromFile(fontFile))
			{
				std::cerr << "Failed to load font. Filepath: " << fontFile << std::endl;
				exit(EXIT_FAILURE);
			}

			file >> fontSize >> RGB.x >> RGB.y >> RGB.z;

			this->m_text.setFont(m_font);
			this->m_text.setCharacterSize(fontSize);
			this->m_text.setFillColor(sf::Color(RGB.x, RGB.y, RGB.z));
		}
		else if (firstToken == "Player")
		{
			file >> this->m_playerConfig.SR \
				 >> this->m_playerConfig.CR \
				 >> this->m_playerConfig.S \
				 >> this->m_playerConfig.FR \
				 >> this->m_playerConfig.FG \
				 >> this->m_playerConfig.FB \
				 >> this->m_playerConfig.OR \
				 >> this->m_playerConfig.OG \
				 >> this->m_playerConfig.OB \
				 >> this->m_playerConfig.OT \
				 >> this->m_playerConfig.V;
		}
		else if (firstToken == "Enemy")
		{
			file >> this->m_enemyConfig.SR \
				 >> this->m_enemyConfig.CR \
				 >> this->m_enemyConfig.SMIN \
				 >> this->m_enemyConfig.SMAX \
				 >> this->m_enemyConfig.OR \
				 >> this->m_enemyConfig.OG \
				 >> this->m_enemyConfig.OB \
				 >> this->m_enemyConfig.OT \
				 >> this->m_enemyConfig.VMIN \
				 >> this->m_enemyConfig.VMAX \
				 >> this->m_enemyConfig.L \
				 >> this->m_enemyConfig.SI;
		}
		else if (firstToken == "Bullet")
		{
			file >> this->m_bulletConfig.SR \
				 >> this->m_bulletConfig.CR \
				 >> this->m_bulletConfig.S \
				 >> this->m_bulletConfig.FR \
				 >> this->m_bulletConfig.FG \
				 >> this->m_bulletConfig.FB \
				 >> this->m_bulletConfig.OR \
				 >> this->m_bulletConfig.OG \
				 >> this->m_bulletConfig.OB \
				 >> this->m_bulletConfig.OT \
				 >> this->m_bulletConfig.V \
				 >> this->m_bulletConfig.L;
		}
	}

	std::string		score {"Score: "};

	score.append(std::to_string(this->m_score));
	this->m_text.setString(score);
	this->m_text.setPosition(10.0f, 5.0f);
	
	this->spawnPlayer();
	return ;
}

void	Game::setPaused(bool paused)
{
	this->m_paused = paused;
	return ;
}

void	Game::sMovement()
{
	sf::Vector2f	playerVelocity;

	if (this->m_player->cInput->getInputStatus("up") == true)
		playerVelocity.y -= this->m_playerConfig.S;
	if (this->m_player->cInput->getInputStatus("left") == true)
		playerVelocity.x -= this->m_playerConfig.S;
	if (this->m_player->cInput->getInputStatus("down") == true)
		playerVelocity.y += this->m_playerConfig.S;
	if (this->m_player->cInput->getInputStatus("right") == true)
		playerVelocity.x += this->m_playerConfig.S;
	for (auto e : this->m_entities.getEntities())
	{
		if (e->getTag() == "player")
			this->m_player->cTransform->setPos(sf::Vector2f(playerVelocity.x, playerVelocity.y));
		else if (e->cTransform)
			e->cTransform->setPos(e->cTransform->getSpeed());
		e->cTransform->setAngle(2.0f);
		e->cShape->getCircle().setRotation(e->cTransform->getAngle());
	}
	return ;
}

void	Game::sUserInput()
{

	sf::Event	event;

	while (this->m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				this->m_running = false;
				break ;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					this->m_running = false;
				else if (event.key.code == sf::Keyboard::P)
					this->m_paused ? this->setPaused(false) : this->setPaused(true);
				else if (event.key.code == sf::Keyboard::W)
					this->m_player->cInput->changeInputStatus("up");
				else if (event.key.code == sf::Keyboard::A)
					this->m_player->cInput->changeInputStatus("left");
				else if (event.key.code == sf::Keyboard::S)
					this->m_player->cInput->changeInputStatus("down");
				else if (event.key.code == sf::Keyboard::D)
					this->m_player->cInput->changeInputStatus("right");
				break ;
			}
			case sf::Event::KeyReleased:
			{
				if (event.key.code == sf::Keyboard::W)
					this->m_player->cInput->changeInputStatus("up");
				else if (event.key.code == sf::Keyboard::A)
					this->m_player->cInput->changeInputStatus("left");
				else if (event.key.code == sf::Keyboard::S)
					this->m_player->cInput->changeInputStatus("down");
				else if (event.key.code == sf::Keyboard::D)
					this->m_player->cInput->changeInputStatus("right");
				break ;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (this->m_player->cInput->getInputStatus("leftMouse") == false)
						this->m_player->cInput->changeInputStatus("leftMouse");
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (this->m_player->cInput->getInputStatus("rightMouse") == false)
						this->m_player->cInput->changeInputStatus("rightMouse");
				}
				break ;
			}
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (this->m_player->cInput->getInputStatus("leftMouse") == false)
						this->m_player->cInput->changeInputStatus("leftMouse");
				}
				break ;
			}
			default:
				break ;
		}
	}
}

void	Game::sLifespan()
{
	for (auto e : this->m_entities.getEntities())
	{
		if (!e->cLifespan)
			continue ;
		if (e->cLifespan->getRemaining() > 0)
				e->cLifespan->setRemaining(e->cLifespan->getRemaining() - 1);
		if (e->isActive() && e->cLifespan->getRemaining() > 0)
		{
			float	alpha_rand {static_cast<float>(e->cLifespan->getRemaining()) / static_cast<float>(e->cLifespan->getTotal())};

			auto 	fill {e->cShape->getCircle().getFillColor()};
			sf::Color newFill {fill.r, fill.g, fill.b, static_cast<sf::Uint8>(255 * alpha_rand)};
			e->cShape->getCircle().setFillColor(newFill);

			auto 	outline {e->cShape->getCircle().getFillColor()};
			sf::Color newOutline {outline.r, outline.g, outline.b, static_cast<sf::Uint8>(255 * alpha_rand)};
			e->cShape->getCircle().setFillColor(newOutline);
		}
		else if (e->cLifespan->getRemaining() <= 0)
			e->destroy();
	}
	return ;
}

void	Game::sRender()
{
	this->m_window.clear();
	for (auto e : this->m_entities.getEntities())
	{
		e->cShape->getCircle().setPosition(e->cTransform->getPos());
		this->m_window.draw(e->cShape->getCircle());
	}
	this->m_window.draw(m_text);
	this->m_window.display();
}

void	Game::sSpawner()
{
	if (this->m_currentFrame - this->m_lastEnemySpawnTime >= this->m_enemyConfig.SI)
		this->spawnEnemy();
	if (this->m_player->cInput->getInputStatus("leftMouse") == true)
	{
		sf::Vector2f	mouseP = sf::Vector2f(((sf::Mouse::getPosition(this->m_window).x)), ((sf::Mouse::getPosition(this->m_window).y)));
		
		this->spawnBullets(this->m_player, mouseP);
		this->m_player->cInput->changeInputStatus("leftMouse");
	}
	if (this->m_player->cInput->getInputStatus("rightMouse") == true)
	{
		this->spawnSpecialWeapon(this->m_player);
		this->m_player->cInput->changeInputStatus("rightMouse");
	}
	return ;
}

void	Game::sCollision()
{
	for (auto player : this->m_entities.getEntities("player"))
	{
		for (auto enemy : this->m_entities.getEntities("enemy"))
		{
			sf::Vector2f	diff {enemy->cTransform->getPos() - player->cTransform->getPos()};
			double			collision_rad {(player->cCollision->getRadius() + enemy->cCollision->getRadius()) * \
										(player->cCollision->getRadius() + enemy->cCollision->getRadius())};
			double			dist {(diff.x * diff.x) + (diff.y * diff.y)};

			if (dist < collision_rad)
			{
				if (player->isActive() == true)
				{
					std::string		score {"Score: "};

					score.append(std::to_string(0));
					this->m_text.setString(score);
					this->m_text.setPosition(10.0f, 5.0f);

					enemy->destroy();
					player->destroy();

					this->spawnPlayer();
				}
			}
		}
		for (auto enemy : this->m_entities.getEntities("smallenemy"))
		{
			sf::Vector2f	diff {enemy->cTransform->getPos() - player->cTransform->getPos()};
			double			collision_rad {(player->cCollision->getRadius() + enemy->cCollision->getRadius()) * \
										(player->cCollision->getRadius() + enemy->cCollision->getRadius())};
			double			dist {(diff.x * diff.x) + (diff.y * diff.y)};

			if (dist < collision_rad)
			{
				if (player->isActive() == true)
				{
					std::string		score {"Score: "};

					score.append(std::to_string(m_score / 2));
					this->m_text.setString(score);
					this->m_text.setPosition(10.0f, 5.0f);

					enemy->destroy();
					player->destroy();

					this->spawnPlayer();
				}
			}
		}
	}
	for (auto bullet : this->m_entities.getEntities("bullet"))
	{
		for (auto enemy : this->m_entities.getEntities("enemy"))
		{
			sf::Vector2f	diff {enemy->cTransform->getPos() - bullet->cTransform->getPos()};
			double			collision_rad {(bullet->cCollision->getRadius() + enemy->cCollision->getRadius()) * \
										(bullet->cCollision->getRadius() + enemy->cCollision->getRadius())};
			double			dist {(diff.x * diff.x) + (diff.y * diff.y)};

			if (dist < collision_rad)
			{
				std::string		score {"Score: "};

				this->m_score = enemy->cScore->getScore();
				score.append(std::to_string(0));
				this->m_text.setString(score);
				this->m_text.setPosition(10.0f, 5.0f);

				this->spawnSmallEnemys(enemy);
				enemy->destroy();
				bullet->destroy();

				break ;
			}
		}
		for (auto enemy : this->m_entities.getEntities("smallenemy"))
		{
			sf::Vector2f	diff {enemy->cTransform->getPos() - bullet->cTransform->getPos()};
			double			collision_rad {(bullet->cCollision->getRadius() + enemy->cCollision->getRadius()) * \
										(bullet->cCollision->getRadius() + enemy->cCollision->getRadius())};
			double			dist {(diff.x * diff.x) + (diff.y * diff.y)};

			if (dist < collision_rad)
			{
				std::string		score {"Score: "};

				this->m_score += enemy->cScore->getScore();
				score.append(std::to_string(this->m_score));
				this->m_text.setString(score);
				this->m_text.setPosition(10.0f, 5.0f);

				enemy->destroy();
				bullet->destroy();

				break ;
			}
		}
	}
	for (auto e : this->m_entities.getEntities())
	{
		if (e->getTag() == "bullet" || e->getTag() == "enemy" || e->getTag() == "smallenemy")
		{
			if (e->cTransform->getPos().x + e->cCollision->getRadius() > m_window.getSize().x)
				e->cTransform->setSpeed(sf::Vector2f(-1, 1));
			else if (e->cTransform->getPos().x - e->cCollision->getRadius() < 0)
				e->cTransform->setSpeed(sf::Vector2f(-1, 1));
			else if (e->cTransform->getPos().y + e->cCollision->getRadius() > m_window.getSize().y)
				e->cTransform->setSpeed(sf::Vector2f(1, -1));
			else if (e->cTransform->getPos().y - e->cCollision->getRadius() < 0)
				e->cTransform->setSpeed(sf::Vector2f(1, -1));
		}
	}
	return ;
}

void	Game::spawnPlayer()
{
	auto			entity = this->m_entities.addEntity("player");
	sf::Vector2f	pos {(this->m_window.getSize().x * 0.5f), (this->m_window.getSize().y * 0.5f)};

	entity->cTransform = std::make_shared<CTransform>(pos, sf::Vector2f(0.0f, 0.0f), 0.0f);
	entity->cShape = std::make_shared<CShape>(this->m_playerConfig.SR, this->m_playerConfig.V, \
												sf::Color(this->m_playerConfig.FR, this->m_playerConfig.FG, \
															this->m_playerConfig.FB), \
												sf::Color(this->m_playerConfig.OR, this->m_playerConfig.OG, \
															this->m_playerConfig.OB), \
												this->m_playerConfig.OT);
	entity->cInput = std::make_shared<CInput>();
	entity->cCollision = std::make_shared<CCollision>(this->m_playerConfig.CR);

	this->m_player = entity;
	return ;
}

void	Game::spawnEnemy(){}
// {
// 	auto			entity = m_entities.addEntity("enemy");

// 	int				minPosX {m_enemyConfig.CR};
// 	int				minPosY {m_enemyConfig.CR};
// 	int				maxPosX {static_cast<int>(m_window.getSize().x - m_enemyConfig.CR)};
// 	int				maxPosY {static_cast<int>(m_window.getSize().y - m_enemyConfig.CR)};
// 	sf::Vector2f	pos {static_cast<float>(minPosX + (rand() % (maxPosX - minPosX + 1))), \
// 						 static_cast<float>(minPosY + (rand() % (maxPosY - minPosY + 1)))};
	
// 	sf::Vector2f	speed = sf::Vector2f((- m_enemyConfig.SMIN + (rand() % static_cast<int>(m_enemyConfig.SMAX + m_enemyConfig.SMIN + 1))), \
// 						   				(- m_enemyConfig.SMIN + (rand() % static_cast<int>(m_enemyConfig.SMAX + m_enemyConfig.SMIN + 1))));

// 	int				vert = m_enemyConfig.VMIN + (rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1));
// 	sf::Color		fill {static_cast<sf::Uint8>(rand() % (256)), static_cast<sf::Uint8>(rand() % (256)), static_cast<sf::Uint8>(rand() % (256))};
// 	sf::Color		outline {static_cast<sf::Uint8>(m_enemyConfig.OR), static_cast<sf::Uint8>(m_enemyConfig.OG), static_cast<sf::Uint8>(m_enemyConfig.OB)};


// 	entity->cTransform = std::make_shared<CTransform>(pos, speed, 0.0f);
// 	entity->cScore = std::make_shared<CScore>(100);
// 	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vert, sf::Color(0, 0, 0), \
// 												sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), \
// 												m_enemyConfig.OT);
// 	entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
	
// 	m_lastEnemySpawnTime = m_currentFrame;
// }

void	Game::spawnSmallEnemys(std::shared_ptr<Entity> e){}
// {
// 	size_t			vert {e->cShape->circle.getPointCount()};
// 	sf::Vector2f	position {e->cTransform->pos.x, e->cTransform->pos.x};

// 	double			p {(double)(std::sqrt((position.x * position.x) + (position.y * position.y)))};
// 	position.x = position.x / p;
// 	position.y = position.y / p;

// 	sf::Color		eFill {e->cShape->circle.getFillColor()};
// 	sf::Color		eOutline {e->cShape->circle.getOutlineColor()};
// 	float			eThick {e->cShape->circle.getOutlineThickness()};

// 	float			smallRad {e->cShape->circle.getRadius() * 0.5f};
// 	float			smallCollRad {e->cCollision->raidus * 0.5f};


// 	for (size_t i = 0; i < vert; i++)
// 	{
// 		auto			ent = m_entities.addEntity("smallenemy");
// 		float			alpha {0};
// 		const double	pi {3.14159265359};
// 		double			rad {0};

// 		ent->cScore = std::make_shared<CScore>(e->cScore->score * 2);
// 		ent->cShape = std::make_shared<CShape>(smallRad, vert, eFill, eOutline, eThick);
// 		ent->cCollision = std::make_shared<CCollision>(smallCollRad);
// 		ent->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
	
// 		rad = (alpha * pi / 180.0);

// 		sf::Vector2f	velo {static_cast<float>(std::cos(rad) * position.x + std::sin(rad) * position.y), \
// 							  static_cast<float>(std::cos(rad) * position.x + std::sin(rad) * position.y)};
// 		sf::Vector2f	normalized = sf::Vector2f(((velo.x) / std::sqrt((velo.x * velo.x) + (velo.y * velo.y))), \
// 												 ((velo.y) / std::sqrt((velo.x * velo.x) + (velo.y * velo.y))));

// 		ent->cTransform = std::make_shared<CTransform>(e->cTransform->pos, normalized, alpha);

// 		alpha += 360 / vert;
// 	}
// }

void	Game::spawnBullets(std::shared_ptr<Entity> entity, const sf::Vector2f& mousePos){}
// {
// 	auto 			bullet = m_entities.addEntity("bullet");

// 	float			angle = std::atan2(-(mousePos.y - entity->cTransform->pos.y), (mousePos.x - entity->cTransform->pos.x));
// 	sf::Vector2f	direction = sf::Vector2f(std::cos(angle), -std::sin(angle));
// 	sf::Vector2f	normalized = sf::Vector2f(((direction.x) / std::sqrt((direction.x * direction.x) + (direction.y * direction.y))), \
// 											 ((direction.y) / std::sqrt((direction.x * direction.x) + (direction.y * direction.y))));

// 	bullet->cTransform = std::make_shared<CTransform>((entity->cTransform->pos), normalized * m_bulletConfig.S, 0);
// 	bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
// 	bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
// 	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, \
// 											  sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), \
// 											  sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), \
// 											  m_bulletConfig.OT);
// }

void	Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity){}
// {
// 	auto 			specialweapon = m_entities.addEntity("specialweapon");

// 	specialweapon->cLifespan = std::make_shared<CLifespan>(3);
// 	specialweapon->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, \
// 													sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), \
// 													sf::Color(0, 255, 0), m_playerConfig.OT);
// 	// specialweapon->cCollision = std::make_shared<CCollision>();
// }
