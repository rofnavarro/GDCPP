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

const int	&CLifespan::getTotal(void) const
{
	return (this->_total);
}

void	CLifespan::setRemaining(int remaining)
{
	this->_remaining = remaining;
	return ;
}

void	CLifespan::setTotal(int total)
{
	this->_total = total;
	return ;
}

bool	CLifespan::isAlive(void)
{
	if (this->_remaining > 0)
		return (true);
	return (false);
}
