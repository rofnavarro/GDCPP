#include	"./include/Entity.hpp"
#include	"./include/EntityManager.hpp"
#include	"./include/Game.hpp"

int	main(void)
{
	Game	*G = new Game("src/config.txt");
	
	G->run();

	delete G;
	return	(0);
}
