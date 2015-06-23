#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>

#include "Model.h"
#include "View.h"

// Include controllers class
#include "Mouse.h"
#include "Keyboard.h"

class Controller
{
public:
	Controller(Model* model, View* view);
	~Controller(void);

	// Get the status of the game boolean flag
	bool RunMainLoop(void);

	// Process input from I/O devices
	bool ProcessInput(void);

	// Handle to the model
	Model* mainModel;

	// Handle to the view
	View* mainView;

	// Handle to various input devices
	Mouse* mouseInput;
	Keyboard* keyboardInput;

protected:
	bool Init();

	bool m_bContinueLoop;
};

#endif