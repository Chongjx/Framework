/******************************************************************************/
/*!
\file	Scene.h
\author Jun Xiang
\brief
Base scene class
*/
/******************************************************************************/
#ifndef SCENE_H
#define SCENE_H

/******************************************************************************/
/*!
		enum SCENE_STATE:
\brief	Define the variuous states that the scene has
*/
/******************************************************************************/
enum SCENE_STATE
{
	SCENE_MENU = 0,
	SCENE_INGAME,
	SCENE_PAUSE,
	SCENE_QUIT,
	SCENE_MAX,
};

/******************************************************************************/
/*!
		Class Scene:
\brief	Polymorphism 
*/
/******************************************************************************/
class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void UpdateCameraStatus(const unsigned char key) = 0;
	virtual void UpdateWeaponStatus(const unsigned char key) = 0;
	virtual void RenderScene() = 0;
	virtual void RenderMiniMap() = 0;
	virtual void Exit() = 0;

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_FIRE,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};

	SCENE_STATE currentScene, prevScene;
};

#endif