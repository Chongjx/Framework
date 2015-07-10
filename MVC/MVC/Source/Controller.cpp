#include "Controller.h"

Controller::Controller(void) : 
	mainModel(NULL),
	mainView(NULL)
{
}

Controller::Controller(Model *mainModel, View *mainView, string controllerSetUp):
	mainModel(mainModel),
	mainView(mainView)
{
}

Controller::~Controller(void)
{
}