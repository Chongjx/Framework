#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
private:
	double current_x, current_y, last_x, last_y, diff_x, diff_y;
	double mouse_yaw, mouse_pitch;
	float sensitivity;

	bool bLButtonState, bRButtonState, bMButtonState;

	float dead_zone;
public:
	Mouse(void);
	~Mouse(void);

	void Init(void);
	bool Update(void);
	bool IsMousePressed(unsigned short key);

	void setMousePos(double new_x, double new_y);
	void getMousePos(void);

	double getCurrentX(void) const;
	double getCurrentY(void) const;

	double getLastX(void) const;
	double getLastY(void) const;

	double getDiffX(void) const;
	double getDiffY(void) const;

	double getMouseYaw(void) const;
	double getMousePitch(void) const;

	void setSensitivity(float sensitivity);
	float getSensitivity(void) const;

	void setLButtonState(bool state);
	bool getLButtonState(void) const;

	void setRButtonState(bool state);
	bool getRButtonState(void) const;

	void setMButtonState(bool state);
	bool getMButtonState(void) const;

	void setDeadZoneSize(float size);
	float getDeadZoneSize(void) const;
};

#endif