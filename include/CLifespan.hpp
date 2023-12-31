#pragma	once

#ifndef CLIFESPAN_HPP
# define CLIFESPAN_HPP

# include	"engine.hpp"

class	CLifespan
{
private:
	int			_remaining {0};
	int			_total {0};

public:

				CLifespan(int total);
				~CLifespan(void);

	const int	&getRemaining(void) const;
	void		setRemaining(int remaining);
	bool		live(void);

};

#endif