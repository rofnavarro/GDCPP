#pragma	once

#ifndef CINPUT_HPP
# define CINPUT_HPP

# include <string>

class	CInput
{
public:
	bool		up {false};
	bool		left {false};
	bool		right {false};
	bool		down {false};
	bool		leftMouse {false};
	bool		rightMouse {false};

				CInput(void);
				~CInput(void);

};

#endif