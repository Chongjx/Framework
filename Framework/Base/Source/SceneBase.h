/******************************************************************************/
/*!
\file	SceneBase.h
\author Jun Xiang
\brief
Class to build ...
*/
/******************************************************************************/
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Application.h"
#include "FPcamera.h"

#include "MeshBuilder.h"

#include "Light.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "Utility.h"
#include "shader.hpp"
#include "LoadTGA.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <irrKlang.h>

using std::string;
using std::cout;
using std::endl;
using std::setprecision;
using std::fixed;
using std::to_string;
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

static const float SKYBOXSIZE = 1000.f;

class SceneBase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,

        // light 1
        U_LIGHT0_TYPE,
        U_LIGHT0_SPOTDIRECTION,
        U_LIGHT0_COSCUTOFF,
        U_LIGHT0_COSINNER,
        U_LIGHT0_EXPONENT,
        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,

        // light 2
        U_LIGHT1_TYPE,
        U_LIGHT1_SPOTDIRECTION,
        U_LIGHT1_COSCUTOFF,
        U_LIGHT1_COSINNER,
        U_LIGHT1_EXPONENT,
        U_LIGHT1_POSITION,
        U_LIGHT1_COLOR,
        U_LIGHT1_POWER,
        U_LIGHT1_KC,
        U_LIGHT1_KL,
        U_LIGHT1_KQ,

        U_LIGHTENABLED,
        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
        U_TOTAL,
	};
	enum OBJ_TYPE
	{
		GEO_AXES,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_QUAD,
		GEO_CUBE,
		GEO_RING,
		GEO_CONE,
		GEO_TEXT,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_OBJECT,
		MAX_OBJ,
	};

	enum SOUND
	{
		FOOTSTEP = 0,
		JUMPING,
		SHOOTING,
		MUSIC,
		SHEEP,
		HORSE,
		FSCREAM,	//female scream 
		MSCREAM,	//male scream
		DOGBARK,
		PICKUP,
		DOORSND,
		DOORCLS,
		LANDING,
		MENUOPEN,
		MENUCLS,
		MENUSCRL,
		STATUE,
		COINSND,
		TOTAL_SOUND,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init(void);
    virtual void Update(double dt);
    virtual void RenderScene(void);
	virtual void RenderMiniMap(void);
    virtual void Exit(void);

	void InitOpenGL(void);
	void InitLights(void);
	void InitMesh(void);
	void InitCamera(void);
	void InitSound(void);
	void InitCharacters(void);
	void InitVariables(void);
	void InitUI(void);
	void ReInit(void);

	void UpdateOpenGL(void);
	void UpdateLights(double dt);
	void UpdateCamera(double dt);
	void UpdateCharacters(double dt);
	void UpdateVariables(double dt);
	void UpdateUI(double dt);
	void UpdateSound(double dt);

	void RenderLights(void);
	void RenderEnvironment(void);
	void RenderCharacters(void);
	void RenderUI(void);

	void Render3DMesh(Mesh *mesh, bool enableLight);
	void Render2DMesh(Mesh* mesh, bool enableLight, float size = 1.0f, float x = 0.0f, float y = 0.0f);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
private:
	unsigned m_vertexArrayID;
	Mesh* meshList[MAX_OBJ];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	static const int NUM_LIGHTS = 2;

	FPcamera camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[NUM_LIGHTS];

	bool bLightEnabled;

	float fps;

	ISoundEngine* engine;
    ISound* snd[TOTAL_SOUND];
};

#endif