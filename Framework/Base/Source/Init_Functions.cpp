/******************************************************************************/
/*!
\file	Init_Functions.cpp
\author Jun Xiang
\brief
Initialize all the scene stuff here
*/
/******************************************************************************/
#include "SceneBase.h"

/******************************************************************************/
/*!
\brief
Init OpenGl variables
*/
/******************************************************************************/
void SceneBase::InitOpenGL(void)
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
}

/******************************************************************************/
/*!
\brief
Init Lights variables
*/
/******************************************************************************/
void SceneBase::InitLights(void)
{
	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader" );
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	// light 1
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");

	// light 2
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights"); 
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	// directional light (sunlight)
	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].exponent = 3.f;
	lights[0].position.Set(1.f, 1.f, 1.f);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1.f;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	// directional light (sunlight)
	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].exponent = 3.f;
	lights[1].position.Set(-1.f, -1.f, -1.f);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1.f;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].spotDirection.Set(0.f, 1.f, 0.f);

	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		glUniform1i(m_parameters[i * 11 + 7], lights[i].type);
		glUniform1f(m_parameters[i * 11 + 9], lights[i].cosCutoff);
		glUniform1f(m_parameters[i * 11 + 10], lights[i].cosInner);
		glUniform1f(m_parameters[i * 11 + 11], lights[i].exponent);
		glUniform3fv(m_parameters[i * 11 + 13], 1, &lights[i].color.r);
		glUniform1f(m_parameters[i * 11 + 14], lights[i].power);
		glUniform1f(m_parameters[i * 11 + 15], lights[i].kC);
		glUniform1f(m_parameters[i * 11 + 16], lights[i].kL);
		glUniform1f(m_parameters[i * 11 + 17], lights[i].kQ);
	}

	//Number of lights in Shader
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
}

/******************************************************************************/
/*!
\brief
Init Meshes
*/
/******************************************************************************/
void SceneBase::InitMesh(void)
{
	for(int i = 0; i < MAX_OBJ; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 10.f);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 1), 1.f);

	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);

	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("LEFT", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("RIGHT", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("TOP", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("BOTTOM", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("FRONT", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//chair.obj");
	meshList[GEO_OBJECT]->textureID = LoadTGA("Image//chair.tga");
}

/******************************************************************************/
/*!
\brief
Init Camera
*/
/******************************************************************************/
void SceneBase::InitCamera(void)
{
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

/******************************************************************************/
/*!
\brief
Init sounds
*/
/******************************************************************************/
void SceneBase::InitSound(void)
{
	// start the sound engine with default parameters
	engine = createIrrKlangDevice();

	// play some sound stream, looped
	snd[FOOTSTEP] = engine->play2D("Wav//FootStep.ogg", true, true);
	snd[JUMPING] = engine->play3D("Wav//Jumping.ogg", vec3df(0, 0, 0), true, true);
	snd[SHOOTING] = engine->play3D("Wav//Gunfire.ogg", vec3df(0, 0, 0), true, true);
	snd[MUSIC] = engine->play3D("Wav//Music.ogg", vec3df(0, 0, 0), true, false, true);
	snd[SHEEP] = engine->play3D("Wav//SheepBleat.ogg", vec3df(-280, 10, -370), true, true);
	snd[HORSE] = engine->play3D("Wav//Horse.ogg", vec3df(0, 0, 0), true, true);
	snd[FSCREAM] = engine->play3D("Wav//Scream_Female.ogg", vec3df(0, 0, 0), true, true);
	snd[MSCREAM] = engine->play3D("Wav//Scream_Male.ogg", vec3df(0, 0, 0), true, true);
	snd[DOGBARK] = engine->play3D("Wav//Dog_Barking.ogg", vec3df(0, 0, 0), true, true);
	snd[MUSIC]->setVolume(5);snd[FOOTSTEP]->setVolume(10000);snd[SHEEP]->setVolume(700);
	snd[PICKUP] = engine->play3D("Wav//PickUp.ogg", vec3df(0, 0, 0), true, true);
	snd[DOORSND] = engine->play3D("Wav//DoorOpen.ogg", vec3df(0, 0, 0), true, true);
	snd[DOORCLS] = engine->play3D("Wav//DoorClose.ogg", vec3df(0, 0, 0), true, true);
	snd[LANDING] = engine->play3D("Wav//Landing.ogg", vec3df(0, 0, 0), true, true);
	snd[MENUOPEN] = engine->play3D("Wav//Inventory.ogg", vec3df(0, 0, 0), true, true);
	snd[MENUCLS] = engine->play3D("Wav//Inventory.ogg", vec3df(0, 0, 0), true, true);
	snd[MENUSCRL] = engine->play3D("Wav//Scrolling.ogg", vec3df(0, 0, 0), true, true);
	snd[STATUE] = engine->play3D("Wav//Statue.ogg", vec3df(0, 0, 0), true, true);
	snd[COINSND] = engine->play3D("Wav//Coin.ogg", vec3df(0, 0, 0), true, true);
}

/******************************************************************************/
/*!
\brief
Init Characters
*/
/******************************************************************************/
void SceneBase::InitCharacters(void)
{
}

/******************************************************************************/
/*!
\brief
Init variables
*/
/******************************************************************************/
void SceneBase::InitVariables(void)
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;
}

/******************************************************************************/
/*!
\brief
Init User Interface
*/
/******************************************************************************/
void SceneBase::InitUI(void)
{
}

/******************************************************************************/
/*!
\brief
Re Init all variables
*/
/******************************************************************************/
void SceneBase::ReInit(void)
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