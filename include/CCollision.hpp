#pragma	once

#ifndef CCOLLISION_HPP
# define CCOLLISION_HPP

# include	"engine.hpp"

class	CCollision
{
private:
	float		_raidus {0};

public:
				CCollision(float r);
				~CCollision(void);

	const float	&getRadius(void) const;

};

#endif