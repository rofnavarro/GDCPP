#include	"include/engine.hpp"

int	main(void)
{
	Game	*G = new Game("src/config.txt");
	
	G->run();

	delete G;
	return	(0);
}
