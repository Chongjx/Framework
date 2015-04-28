#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;
	static bool getMouseUpdate();

private:
	Application();
	~Application();

	//Declare a window object
	StopWatch m_timer;
	const static int m_window_deadzone = 50;
	const static int m_window_width = 1366;
	const static int m_window_height = 768;
};

#endif