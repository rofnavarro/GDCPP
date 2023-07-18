#include	"include/engine.hpp"

int	main(void)
{
	sf::RenderWindow	win(sf::VideoMode(1920, 1080), "GAME ENGINE v0.1");

	while (win.isOpen())
	{
		sf::Event	event;
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				win.close();
		}
		win.clear(sf::Color::Cyan);
		win.display();
	}


	return	(0);
}
