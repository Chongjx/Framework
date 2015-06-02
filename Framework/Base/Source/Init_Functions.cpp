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
	m_programID = LoadShaders( "Shader//Fog.vertexshader", "Shader//Fog.fragmentshader" );

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
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR0_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled[0]");
	m_parameters[U_COLOR0_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");
	m_parameters[U_COLOR1_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled[1]");
	m_parameters[U_COLOR1_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[1]");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Get a handle for fog uniform
	m_parameters[U_FOG_COLOR] = glGetUniformLocation(m_programID, "fog.color");
	m_parameters[U_FOG_START] = glGetUniformLocation(m_programID, "fog.start");
	m_parameters[U_FOG_END] = glGetUniformLocation(m_programID, "fog.end");
	m_parameters[U_FOG_DENSITY] = glGetUniformLocation(m_programID, "fog.density");
	m_parameters[U_FOG_TYPE] = glGetUniformLocation(m_programID, "fog.type");
	m_parameters[U_FOG_ENABLED] = glGetUniformLocation(m_programID, "fog.enabled");

	glUseProgram(m_programID);

	// directional light (sunlight)
	lights[0].type = Light::LIGHT_POINT;
	lights[0].exponent = 3.f;
	lights[0].position.Set(0.f, 200.f, 0.f);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 100.f;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	// directional light (sunlight)
	lights[1].type = Light::LIGHT_POINT;
	lights[1].exponent = 3.f;
	lights[1].position.Set(0.f, 200.f, 0.f);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 100.f;
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

	Color fogColor(0.913f, 0.725f, 0.549f);
	glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	glUniform1f(m_parameters[U_FOG_START], 200);
	glUniform1f(m_parameters[U_FOG_END], 2000);
	glUniform1f(m_parameters[U_FOG_DENSITY], 0.005f);
	glUniform1f(m_parameters[U_FOG_TYPE], 2);
	// Disable fog
	glUniform1f(m_parameters[U_FOG_ENABLED], bFogEnabled);

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
	for(int i = 0; i < GEO_MAX; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 0), 18, 36, 1.f);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureID[0] = LoadTGA("Image//cover.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 1), 1.f);

	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID[0] = LoadTGA("Image//starwars.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);

	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("cursor", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_CURSOR]->textureID[0] = LoadTGA("Image//cursor.tga");

	meshList[GEO_PISTOLCH] = MeshBuilder::GenerateQuad("cursor", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_PISTOLCH]->textureID[0] = LoadTGA("Image//pistolch.tga");

	meshList[GEO_RIFLECH] = MeshBuilder::GenerateQuad("cursor", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_RIFLECH]->textureID[0] = LoadTGA("Image//riflech.tga");

	meshList[GEO_SNIPERCH] = MeshBuilder::GenerateQuad("cursor", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_SNIPERCH]->textureID[0] = LoadTGA("Image//sniperch.tga");

	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("skyplane", Color(1, 1, 1), 128, 2000.0f, 4000.f, 1.0f, 1.0f);
	meshList[GEO_SKYPLANE]->textureID[0] = LoadTGA("Image//top.tga");

	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("terrain", "Image//heightmap.raw", m_heightMap);
	meshList[GEO_TERRAIN]->textureID[0] = LoadTGA("Image//sand.tga");

	meshList[GEO_PLATFORM] = MeshBuilder::GenerateOBJ("platform", "OBJ//platform.obj");
	meshList[GEO_PLATFORM]->textureID[0] = LoadTGA("Image//concrete.tga");
	meshList[GEO_PLATFORM]->textureID[1] = LoadTGA("Image//crack.tga");
	meshList[GEO_PLATFORM]->material.kSpecular.Set(0.f, 0.f, 0.f);

	meshList[GEO_CRATE] = MeshBuilder::GenerateOBJ("crate", "OBJ//crate.obj");
	meshList[GEO_CRATE]->textureID[0] = LoadTGA("Image//crate.tga");
	meshList[GEO_CRATE]->textureID[1] = LoadTGA("Image//rough.tga");

	meshList[GEO_SANDBAG] = MeshBuilder::GenerateOBJ("sandbag", "OBJ//sandbag.obj");
	meshList[GEO_SANDBAG]->textureID[0] = LoadTGA("Image//sandbag.tga");

	meshList[GEO_PLAYER] = MeshBuilder::GenerateCube("player", Color(1, 1, 0), 20.f);

	meshList[GEO_PISTOL] = MeshBuilder::GenerateOBJ("pistol", "OBJ//pistol.obj");
	meshList[GEO_PISTOL]->textureID[0] = LoadTGA("Image//pistol.tga");

	meshList[GEO_RIFLE] = MeshBuilder::GenerateOBJ("rifle", "OBJ//rifle.obj");
	meshList[GEO_RIFLE]->textureID[0] = LoadTGA("Image//rifle.tga");

	meshList[GEO_SNIPER] = MeshBuilder::GenerateOBJ("sniper", "OBJ//sniper.obj");
	meshList[GEO_SNIPER]->textureID[0] = LoadTGA("Image//sniper.tga");

	meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("wreckedship", "OBJ//ship.obj");
	meshList[GEO_SHIP]->textureID[0] = LoadTGA("Image//ship.tga");

	meshList[GEO_DEBUG] = MeshBuilder::GenerateDebugBox("debug", Color(0.f, 0.f, 0.f), 1.f);
}

/******************************************************************************/
/*!
\brief
Init Camera
*/
/******************************************************************************/
void SceneBase::InitCamera(void)
{
	player.camera.Init(
		Vector3(0, 25 + TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, 0/TERRAIN_SCALE.x, 0/TERRAIN_SCALE.z), 0), 
		Vector3(0, 25 + TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, 0/TERRAIN_SCALE.x, 0/TERRAIN_SCALE.z), 10), 
		Vector3(0, 1, 0));
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
	player.setMesh(meshList[GEO_CUBE]);
	threeDhitbox body(Vector3(player.camera.getPosition().x, player.camera.getPosition().y, player.camera.getPosition().z), 20.f, 20.f, 20.f, "player");
	player.setHitBox(body);
	player.setRender(true);
}

/******************************************************************************/
/*!
\brief
Init Weapons
*/
/******************************************************************************/
void SceneBase::InitWeapons(void)
{
	ResetTRS(TRS);
	// Init weapon pos
	TRS.translation.SetToTranslation(-0.75f, -0.5f, 2);
	TRS.rotation.SetToRotation(90, 0, 1, 0);
	player.bagpack.pistol.setTRS(TRS);
	player.bagpack.pistol.setMesh(meshList[GEO_PISTOL]);
	player.bagpack.pistol.setReflectLight(false);

	ResetTRS(TRS);

	TRS.translation.SetToTranslation(-0.75f, -0.5f, 2);
	TRS.rotation.SetToRotation(90, 0, 1, 0);
	player.bagpack.rifle.setTRS(TRS);
	player.bagpack.rifle.setMesh(meshList[GEO_RIFLE]);
	player.bagpack.rifle.setReflectLight(false);

	ResetTRS(TRS);

	TRS.translation.SetToTranslation(-0.75f, -0.5f, 2);
	TRS.rotation.SetToRotation(90, 0, 1, 0);
	player.bagpack.sniper.setTRS(TRS);
	player.bagpack.sniper.setMesh(meshList[GEO_SNIPER]);
	player.bagpack.sniper.setReflectLight(false);
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
	bFogEnabled = false;
	bDebugMode = true;
	leaving = false;

	m_Minimap = NULL;

	Properties TRS;

	//Construct 50 environment objects
	for (int i = 0; i < 50; ++i)
	{
		environmentList.push_back(new threeDObject());
	}

	//Construct 10 character
	for (int i = 0; i < 10; ++i)
	{
		characterList.push_back(new Character());
	}

	//Construct 100 bullets
	TRS.scale.SetToScale(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < 100; ++i)
	{
		bulletList.push_back(new Bullet());
		bulletList[i]->setTRS(TRS);
		bulletList[i]->setMesh(meshList[GEO_SPHERE]);
	}

	// Init all environment objs here
	ResetTRS(TRS);

	threeDObject* wreckedShip = fetchEnvironment();
	TRS.rotation.SetToRotation(80, 1, 1, 0);
	wreckedShip->setObjName("wreckedShip");
	wreckedShip->setMesh(meshList[GEO_SHIP]);
	wreckedShip->setTRS(TRS);
	wreckedShip->setReflectLight(false);
	wreckedShip->setPosition(Vector3(0, 100, 200));
	wreckedShip->setHitBox(threeDhitbox(Vector3(0, 0, 0), 195.f, 55.f, 290.f, "wreckShip"));
	wreckedShip->updateHitbox();

	ResetTRS(TRS);
}

/******************************************************************************/
/*!
\brief
Init User Interface
*/
/******************************************************************************/
void SceneBase::InitUI(void)
{
	m_Minimap = new MiniMap();
	m_Minimap->SetBackground(MeshBuilder::GenerateMinimap("Minimap", Color(1, 1, 1), 1.f));
	m_Minimap->GetBackground()->textureID[0] = LoadTGA("Image//sand.tga");
	m_Minimap->SetBorder(MeshBuilder::GenerateMinimapBorder("MinimapBorder", Color(0, 0, 0), 1.f));
	m_Minimap->SetAvatar(MeshBuilder::GenerateMinimapAvatar("MinimapAvatar", Color(1, 0, 0), 1.f));
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

void SceneBase::ResetTRS(Properties &TRS)
{
	TRS.modelProperties.SetToIdentity();
	TRS.translation.SetToIdentity();
	TRS.rotation.SetToIdentity();
	TRS.scale.SetToIdentity();
}

threeDObject* SceneBase::fetchEnvironment(void)
{
	//Fetch an object from the list and return it
	for(std::vector<threeDObject *>::iterator it = environmentList.begin(); it != environmentList.end(); ++it)
	{
		threeDObject *go = (threeDObject*) *it;
		if(go->getRender() == false)
		{
			go->setRender(true);
			go->setVelocity(Vector3(0, 0, 0));
			return go;
		}
	}

	//Handle the situation whenever the list runs out of objects
	for (int i = 0; i < 10; ++i)
	{
		threeDObject *go = new threeDObject;
		go->setType(GO_ENVIRONMENT);
		environmentList.push_back(go);
	}

	threeDObject *go = environmentList.back();
	go->setRender(true);
	return go;
}

Character* SceneBase::fetchCharacter(void)
{
	//Fetch an object from the list and return it
	for(std::vector<Character *>::iterator it = characterList.begin(); it != characterList.end(); ++it)
	{
		Character *go = (Character*) *it;
		if(go->getRender() == false)
		{
			go->setRender(true);
			go->setVelocity(Vector3(0, 0, 0));
			return go;
		}
	}

	//Handle the situation whenever the list runs out of objects
	for (int i = 0; i < 10; ++i)
	{
		Character *go = new Character;
		go->setType(GO_CHARACTER);
		characterList.push_back(go);
	}

	Character *go = characterList.back();
	go->setRender(true);
	return go;
}

Bullet* SceneBase::fetchBullet(void)
{
	//Fetch an object from the list and return it
	for(std::vector<Bullet *>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		Bullet *go = (Bullet*) *it;
		if(go->getRender() == false)
		{
			go->setRender(true);
			go->setStatus(true);
			go->setVelocity(Vector3(0, 0, 0));

			go->setTRS(TRS);

			return go;
		}
	}

	//Handle the situation whenever the list runs out of objects
	for (int i = 0; i < 10; ++i)
	{
		Bullet *go = new Bullet;
		go->setType(GO_BULLET);
		bulletList.push_back(go);
	}

	Bullet *go = bulletList.back();
	go->setRender(true);
	go->setStatus(true);
	return go;
}