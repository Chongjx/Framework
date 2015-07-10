#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include "Model.h"

class View
{
private:
	Model* mainModel;

public:
	View(void);
	View(Model* mainModel, const string viewSetUp);
	virtual ~View(void);
};

#endif