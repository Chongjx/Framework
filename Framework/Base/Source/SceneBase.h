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
#include "Character.h"
#include "twoDObject.h"
#include "Particle.h"

#include "MeshBuilder.h"
#include "SpriteAnimation.h"
#include "Light.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "Utility.h"
#include "shader.hpp"
#include "LoadTGA.h"
#include "LoadHmap.h"
#include "MiniMap.h"

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
static const Vector3 TERRAIN_SCALE(4000.f, 350.f, 4000.f);
static const float MINIMAP_SCALE = 57.5f;
static const int FONT_SIZE = 3;
static const float REPULSE_FORCE = 20.f;

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
        U_COLOR0_TEXTURE_ENABLED,
		U_COLOR0_TEXTURE,
		U_COLOR1_TEXTURE_ENABLED,
		U_COLOR1_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,

		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLED,
        U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_QUAD,
		GEO_CUBE,
		GEO_RING,
		GEO_CONE,
		GEO_CURSOR,
		GEO_BULLET,
		GEO_PISTOLCH,
		GEO_RIFLECH,
		GEO_SNIPERCH,
		GEO_HEALTHBAR,
		GEO_SKYPLANE,
		GEO_TERRAIN,
		GEO_PLATFORM,
		GEO_CRATE,
		GEO_SANDBAG,
		GEO_PLAYER,
		GEO_ALIEN,
		GEO_CHARACTER,
		GEO_PISTOL,
		GEO_RIFLE,
		GEO_SNIPER,
		GEO_SHIP,
		GEO_BUILDINGS,
		GEO_TEXT,
		GEO_OBJECT,
		GEO_TREE,
		GEO_DEBUG,
		GEO_MAX,
	};

	enum SOUND
	{
		WALKING = 0,
		PANTING,
		BEATING,
		FIREPISTOL,
		FIRERIFLE,
		RELOADPISTOL,
		RELOADRIFLE,
		RADIO,
		ALIEN,
		HEALTHBONUS,
		PISTOLBONUS,
		RIFLEBONUS,
		ATTACKED,
		//GAMEOVER,
		//MUSIC,
		TOTAL_SOUND,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init(void);
    virtual void Update(double dt);
	virtual void UpdateCameraStatus(const unsigned char key);
	virtual void UpdateWeaponStatus(const unsigned char key);
	virtual void UpdateSoundStatus(const unsigned char key);
    virtual void RenderScene(void);
    virtual void Exit(void);

	void InitOpenGL(void);
	void InitLights(void);
	void InitMesh(void);
	void InitCamera(void);
	void InitSound(void);
	void InitCharacters(void);
	void InitWeapons(void);
	void InitVariables(void);
	void InitUI(void);
	void ReInit(void);
	void ResetTRS(Properties &TRS);

	void UpdateOpenGL(void);
	void UpdateLights(double dt);
	void UpdateMovement(double dt);
	void UpdateCharacters(double dt);
	void UpdateWeapons(double dt);
	void UpdateVariables(double dt);
	void UpdateCollisions(double dt);
	void UpdateUI(double dt);

	void SetCamera(void);
	void RenderLights(void);
	void RenderSkyPlane(void);
	void RenderTerrain(void);
	void RenderEnvironment(void);
	void RenderCharacters(void);
	void RenderWeapons(void);
	void RenderBullets(void);
	void RenderUI(void);
	void RenderMiniMap(void);

	// Toggle HUD mode
	void SetHUD(const bool m_bHUDmode);

	void Render3DMesh(Mesh *mesh, bool enableLight);
	void Render2DMesh(Mesh* mesh, bool enableLight, float size, float x = 0.0f, float y = 0.0f, float rotate = 0.0f);
	void Render2DMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	threeDObject* fetchEnvironment(void);
	Character* fetchCharacter(void);
	Bullet* fetchBullet(void);
	Particle* fetchParticle(void);
	
private:
	unsigned m_vertexArrayID;
	Mesh* meshList[GEO_MAX];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	vector<unsigned char>m_heightMap;
	// handle to the minimap
	MiniMap* m_Minimap;
	Avatar newAvatar;

	static const int NUM_LIGHTS = 2;

	Character player;
	FPcamera tempCamera;
	unsigned wave;
	unsigned enemyCount;
	unsigned maxEnemy;
	Properties TRS;
	float startTimer;
	float timer;
	int itemBonus;
	string displayBonus;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[NUM_LIGHTS];

	bool bLightEnabled;
	bool bFogEnabled;
	bool bDebugMode;

	float fps;
	bool leaving;

	ISoundEngine* engine;
    ISound* snd[TOTAL_SOUND];

	Weapon pistol;

	vector<threeDObject *> environmentList;
	vector<Character *> characterList;
	vector<Bullet *> bulletList;
	vector<Particle *> particleList;
	vector<GameObject *> billboardList;
};

#endif