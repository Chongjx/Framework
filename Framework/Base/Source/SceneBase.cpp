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
	InitWeapons();
	InitVariables();
	InitUI();
}

void SceneBase::Update(double dt)
{
	if (restart)
	{
		ReInit();
	}
	else
	{
		UpdateOpenGL();
		UpdateLights(dt);
		if (!gameOver)
		{
			UpdateMovement(dt);
			UpdateCharacters(dt);
			UpdateWeapons(dt);
			UpdateVariables(dt);
			UpdateCollisions(dt);
		}
		UpdateUI(dt);
	}
}

void SceneBase::RenderScene()
{
	SetCamera();
	RenderLights();
	RenderEnvironment();
	RenderCharacters();
	RenderBullets();
	RenderUI();
}

void SceneBase::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < GEO_MAX; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}

	if (m_Minimap)
	{
		delete m_Minimap;
		m_Minimap = NULL;
	}

	while(environmentList.size() > 0)
	{
		threeDObject *go = environmentList.back();
		delete go;
		environmentList.pop_back();
	}

	while(characterList.size() > 0)
	{
		Character *go = characterList.back();
		delete go;
		characterList.pop_back();
	}

	while(bulletList.size() > 0)
	{
		Bullet *go = bulletList.back();
		delete go;
		bulletList.pop_back();
	}

	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	engine->drop(); // delete engine
}
