#include "View.h"

View::View(void) :
	mainModel(NULL)
{
}

View::View(Model* mainModel, const string viewSetUp) :
	mainModel(mainModel)
{
}

View::~View(void)
{
}