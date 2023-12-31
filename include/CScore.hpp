#pragma	once

#ifndef CSCORE_HPP
# define CSCORE_HPP

# include	"engine.hpp"

class	CScore
{
private:
	int			_score {0};

public:
				CScore(int s);
				~CScore(void);

	const int	&getScore(void) const;
	void		setScore(int score);

};

#endif