#include	"../include/CInput.hpp"

CInput::CInput(void)
{
	return ;
}

CInput::~CInput(void)
{
	return ;
}

const bool	&CInput::getInputStatus(std::string button) const
{
	if (button == "up")
		return (this->_up);
	else if (button == "left")
		return (this->_left);
	else if (button == "right")
		return (this->_right);
	else if (button == "down")
		return (this->_down);
	else if (button == "leftMouse")
		return (this->_leftMouse);
	return (this->_rightMouse);
}

void	CInput::changeInputStatus(std::string button)
{
	if (button == "up")
	{
		if (this->_up == true)
			this->_up = false;
		else
			this->_up = true;
	}
	else if (button == "left")
	{
		if (this->_left == true)
			this->_left = false;
		else
			this->_left = true;
	}
	else if (button == "right")
	{
		if (this->_right == true)
			this->_right = false;
		else
			this->_right = true;
	}
	else if (button == "down")
	{
		if (this->_down == true)
			this->_down = false;
		else
			this->_down = true;
	}
	else if (button == "leftMouse")
	{
		if (this->_leftMouse == true)
			this->_leftMouse = false;
		else
			this->_leftMouse = true;
	}
	else if (button == "rightMouse")
	{
		if (this->_rightMouse == true)
			this->_rightMouse = false;
		else
			this->_rightMouse = true;
	}
	return ;
}
