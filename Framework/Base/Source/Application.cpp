#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* m_window;
const unsigned char FPS = 120; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

double Application::mouse_current_x = 0.0;
double Application::mouse_current_y = 0.0;
double Application::mouse_diff_x = 0.0;
double Application::mouse_diff_y = 0.0;
double Application::mouse_last_x = 0.0;
double Application::mouse_last_y = 0.0;
double Application::camera_pitch = 0.0;
double Application::camera_yaw = 0.0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}

bool Application::GetMouseUpdate(void)
{
	glfwGetCursorPos(m_window, &mouse_current_x, &mouse_current_y);

	// Calculate the difference in positions
	mouse_diff_x = mouse_current_x - mouse_last_x;
	mouse_diff_y = mouse_current_y - mouse_last_y;

	static bool firstRun = true;

	if (firstRun)
	{
		mouse_diff_x = 0;
		mouse_diff_y = 0;

		firstRun = false;
	}

	//Calculate yaw and pitch
	camera_yaw = (float)mouse_diff_x * 0.0174555555;	// * 3.142f/180.f
	camera_pitch = (float)mouse_diff_y * 0.0174555555;	// * 3.142f/180.f

	// Do a wraparound if the mouse cursor has gone out of the dead zone
	if((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width - m_window_deadzone))
	{
		mouse_current_x = m_window_width >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}

	if((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height - m_window_deadzone))
	{
		mouse_current_y = m_window_height >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}

	// Store the current position as the last position
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;

	if (mouse_diff_x < 0)
	{
		scene->UpdateCameraStatus('j');
	}

	else if (mouse_diff_x > 0)
	{
		scene->UpdateCameraStatus('l');
	}

	if (mouse_diff_y < 0)
	{
		scene->UpdateCameraStatus('k');
	}

	else if (mouse_diff_y > 0)
	{
		scene->UpdateCameraStatus('i');
	}

	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		scene->UpdateWeaponStatus(scene->WA_FIRE);
		scene->UpdateSoundStatus('f');
	}

	else if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		scene->UpdateWeaponStatus(scene->WA_CHANGEWEAPON);
	}

	else
	{
		scene->UpdateWeaponStatus(scene->WA_NIL);
	}

	if (scene->gameOver && glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) ==GLFW_PRESS)
	{
		scene->restart = true;
	}

	return false;
}

bool Application::GetKeyboardUpdate()
{
	if (IsKeyPressed('A'))
	{
		scene->UpdateCameraStatus('a');
		scene->UpdateSoundStatus('a');
	}

	if (IsKeyPressed('D'))
	{
		scene->UpdateCameraStatus('d');
		scene->UpdateSoundStatus('d');
	}

	if (IsKeyPressed('W'))
	{
		scene->UpdateCameraStatus('w');
		scene->UpdateSoundStatus('w');
	}

	if (IsKeyPressed('S'))
	{
		scene->UpdateCameraStatus('s');
		scene->UpdateSoundStatus('s');
	}

	if (IsKeyPressed('Q'))
	{
		scene->UpdateCameraStatus('q');
	}

	if (IsKeyPressed('E'))
	{
		scene->UpdateCameraStatus('e');
	}

	if(IsKeyPressed(VK_SPACE))
	{
		scene->UpdateCameraStatus(32);
		scene->UpdateSoundStatus(32);
	}

	if(IsKeyPressed(VK_LCONTROL))
	{
		scene->UpdateCameraStatus('c');
	}

	if(IsKeyPressed('R'))
	{
		scene->UpdateWeaponStatus(scene->WA_RELOAD);
	}

	if (IsKeyPressed(VK_LSHIFT))
	{
		scene->UpdateCameraStatus('z');
		scene->UpdateSoundStatus('z');
	}

	return true;
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Create a window and create its OpenGL context
	//m_window = glfwCreateWindow(m_window_width, m_window_height, "DM2231_Framework", glfwGetPrimaryMonitor(), NULL);
	m_window = glfwCreateWindow(m_window_width, m_window_height, "DM2231_Framework", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

int Application::GetWindowWidth()
{
	return m_window_width;
}

int Application::GetWindowHeight()
{
	return m_window_height;
}

void Application::Run()
{
	//Main Loop
	scene = new SceneBase();
	scene->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		// Get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;

		if (m_dAccumulatedTime_ThreadOne > 0.016)
		{
			GetKeyboardUpdate();
			GetMouseUpdate();
			scene->Update(m_dElapsedTime);
			m_dAccumulatedTime_ThreadOne = 0.0;
		}

		if (m_dAccumulatedTime_ThreadTwo > 0.03)
		{
			// update ai
			m_dAccumulatedTime_ThreadTwo = 0.0;
		}
		scene->RenderScene();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
