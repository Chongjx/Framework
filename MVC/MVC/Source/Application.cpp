#include "View.h"
#include "Controller.h"

int main(void)
{
	// Change model depending on module
	Model* mainModel = new Model();
	// Model* mainModel = new Modelcomg();
	// Model* mainModel = new Modelgdev();
	// Model* mainModel = new Modelphy();

	// Change view depending on requirement
	View* mainView = new View(mainModel);
	// View mainView = new OpenGLView(mainModel);
	// View mainView = new DX12View(mainModel);

	// Create controller to handle inputs and modify data
	Controller* mainController = new Controller(mainModel, mainView);

	// run game loop
	mainController->RunMainLoop();

	// clean up before closing
	if (mainController != NULL)
	{
		delete mainController;
		mainController = NULL;
	}

	if (mainView != NULL)
	{
		delete mainView;
		mainView = NULL;
	}

	if (mainModel != NULL)
	{
		delete mainModel;
		mainModel = NULL;
	}

	return 0;
}