#include	"../include/CCollision.hpp"

CCollision::CCollision(float r)
:_raidus(r)
{
	return ;
}

CCollision::~CCollision(void)
{
	return ;
}

const float	&CCollision::getRadius(void) const
{
	return (this->_raidus);
}
