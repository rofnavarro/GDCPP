#pragma	once

#ifndef CLIFESPAN_HPP
# define CLIFESPAN_HPP

class	CLifespan
{
private:
	int			_remaining {0};
	int			_total {0};

public:
				CLifespan(int total);
				~CLifespan(void);

	const int	&getRemaining(void) const;
	const int	&getTotal(void) const;
	void		setRemaining(int remaining);
	void		setTotal(int total);
	bool		isAlive(void);

};

#endif