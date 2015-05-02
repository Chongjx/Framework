#include "SceneBase.h"

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	InitOpenGL();
	InitLights();
	InitMesh();
	InitCamera();
	InitSound();
	InitCharacters();
	InitVariables();
	InitUI();
}

void SceneBase::Update(double dt)
{
	UpdateOpenGL();
	UpdateLights(dt);
	UpdateCamera(dt);
	UpdateCharacters(dt);
	UpdateVariables(dt);
	UpdateUI(dt);
	UpdateSound(dt);
}

void SceneBase::RenderScene()
{
	SetCamera();
	RenderLights();
	RenderEnvironment();
	RenderCharacters();
	RenderUI();
}

/******************************************************************************/
/*!
\brief
render a map
*/
/******************************************************************************/
void SceneBase::RenderMiniMap()
{
	//glDisable(GL_DEPTH_TEST);

	/*if(currentScene != SCENE_MENU)
	{
		static int width, height;

		glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

		Mtx44 projection;
		projection.SetToOrtho(-width/15, width/15, -height/15, height/15, -10, 800);
		//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
		projectionStack.LoadMatrix(projection);

		viewStack.LoadIdentity();
		viewStack.LookAt(topdownCam.position.x, topdownCam.position.y, topdownCam.position.z, topdownCam.target.x, topdownCam.target.y, topdownCam.target.z, topdownCam.up.x, topdownCam.up.y, topdownCam.up.z);

		RenderLights();
		RenderBullet(); 
        RenderEnvironment();
		RenderCharacters();
		RenderPlayer();
		RenderMarketStuff();
	}*/
}

void SceneBase::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < GEO_MAX; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	engine->drop(); // delete engine
}
