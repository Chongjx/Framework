#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "SceneBase.h"

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
	static bool IsMousePressed(unsigned short key);
	bool GetMouseUpdate();
	bool GetKeyboardUpdate();
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;

private:
	Application();
	~Application();

	//Declare a window object
	const static int m_window_deadzone = 200;
	const static int m_window_width = 1920;
	const static int m_window_height = 1080;

	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

	// The handler for the scene
	Scene *scene;
};

#endif