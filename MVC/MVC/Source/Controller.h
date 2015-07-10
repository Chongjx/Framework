#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include "Model.h"
#include "View.h"
#include "timer.h"

class Controller
{
private:
	Model* mainModel;
	View* mainView;

public:
	Controller(void);
	Controller(Model *mainModel, View *mainView, string controllerSetUp);
	virtual ~Controller(void);


};

#endif