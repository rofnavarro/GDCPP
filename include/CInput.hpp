#pragma	once

#ifndef CINPUT_HPP
# define CINPUT_HPP

# include <string>

class	CInput
{
private:
	bool		_up {false};
	bool		_left {false};
	bool		_right {false};
	bool		_down {false};
	bool		_leftMouse {false};
	bool		_rightMouse {false};

public:
				CInput(void);
				~CInput(void);

	const bool	&getInputStatus(std::string button) const;
	void		changeInputStatus(std::string button);

};

#endif