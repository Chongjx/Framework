#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"

using std::cout;
using std::endl;

void DisplayMsg(string msg)
{
	cout << msg << endl;
	msg = "";
}

void main(void)
{
	Branch SCENE = BaseReader::FileToRead("Reader//READMAIN.txt");

	// To prevent multiple M/V/C being init and overwritten
	bool initModel, initView, initController;

	Model* mainModel;
	View* mainView;
	Controller* mainController;
	initModel = initView = initController = false;

	string msg;

	for (vector<Branch>::iterator branch = SCENE.childBranches.begin(); branch != SCENE.childBranches.end(); ++branch)
	{
		if (branch->branchName == "Model" && !initModel)
		{
			mainModel = new Model(branch->attributes[0].value);
			initModel = true;

			msg = "Model created: " + branch->attributes[0].value;
			DisplayMsg(msg);
		}

		else if (branch->branchName == "View" && !initView)
		{
			mainView = new View(mainModel, branch->attributes[0].value);
			initView = true;

			msg = "View created: " + branch->attributes[0].value;
			DisplayMsg(msg);
		}

		else if (branch->branchName == "Controller" && !initController)
		{
			mainController = new Controller(mainModel, mainView, branch->attributes[0].value);
			initController = true;

			msg = "Controller created: " + branch->attributes[0].value;
			DisplayMsg(msg);
		}

		else
		{
			msg = "Undefined branch: " + branch->attributes[0].value;
			DisplayMsg(msg);
		}
	}

	//mainController->runMainLoop();

	if (mainController != NULL)
	{
		delete mainController;
		mainController = NULL;

		msg = "Controller deleted!";
		DisplayMsg(msg);
	}

	if (mainView != NULL)
	{
		delete mainView;
		mainView = NULL;

		msg = "View deleted!";
		DisplayMsg(msg);
	}

	if (mainModel != NULL)
	{
		delete mainModel;
		mainModel = NULL;

		msg = "Model deleted!";
		DisplayMsg(msg);
	}
}