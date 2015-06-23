#ifndef VIEW_H
#define VIEW_H

#include "timer.h"

#include <GL/glew.h>
#include <GLFW\/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "Model.h"

GLFWwindow* m_window;
const unsigned char FPS = 120;	// FPS of this game
const unsigned int frameTime = 1000/FPS;	// Time for each frame

class View
{
public:
	View(Model* model);
	~View(void);

	bool InitGL(void);
	bool Createwindow(void);
	void Render(void);

	void TwoDRenderer(void);
	void ThreeDRenderer(void);
	void TextRenderer(void);
};

#endif