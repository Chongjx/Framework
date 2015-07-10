#ifndef MOUSE_H
#define MOUSE_H

#include "GLFW\glfw3.h"

class Mouse
{
private:
	double current_x, current_y;
	double last_x, last_y;
	double diff_x, diff_y;
	bool bLButtonStatus, bRButtonStatus, bMButtonStatus;
	double mouse_yaw, mouse_pitch;

public:
	Mouse();
	~Mouse();

	void setMousePos(const double xCoord, const double yCoord);
	void getMousePos(void);

	//void 
};

#endif