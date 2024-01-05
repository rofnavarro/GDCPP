#include	"../include/CScore.hpp"

CScore::CScore(int s)
:_score(s)
{
	return ;
}

CScore::~CScore(void)
{
	return ;
}

const int	&CScore::getScore(void) const
{
	return (this->_score);
}

void	CScore::setScore(int score)
{
	this->_score += score;
	return ;
}
