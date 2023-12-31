#include	"../include/CLifespan.hpp"

CLifespan::CLifespan(int total)
:_remaining(total), _total(total)
{
	return ;
}

CLifespan::~CLifespan(void)
{
	return ;
}

const int	&CLifespan::getRemaining(void) const
{
	return (this->_remaining);
}

void	CLifespan::setRemaining(int remaining)
{
	this->_remaining = remaining;
	return ;
}

bool	CLifespan::live(void)
{
	if (this->_remaining > 0)
		return (true);
	return (false);
}
