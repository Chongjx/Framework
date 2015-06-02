/******************************************************************************/
/*!
\file	Update_Functions.cpp
\author Jun Xiang
\brief
Update all the scene stuff here
*/
/******************************************************************************/
#include "SceneBase.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Update OpenGL variables

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateOpenGL(void)
{
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);

	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);

	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if(Application::IsKeyPressed('N'))
		bDebugMode = true;
	if(Application::IsKeyPressed('M'))
		bDebugMode = false;
}

/******************************************************************************/
/*!
\brief
Update Lights position and properties

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateLights(double dt)
{
	if(Application::IsKeyPressed('5'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('6'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('7'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('8'))
	{
		bLightEnabled = true;
	}
	else if(Application::IsKeyPressed('9'))
	{
		bLightEnabled = false;
	}

	if(Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(10.f * dt);
	if(Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(10.f * dt);
	if(Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(10.f * dt);
	if(Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(10.f * dt);
	if(Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(10.f * dt);
	if(Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(10.f * dt);
}

/******************************************************************************/
/*!
\brief
Update Camera position and target

\param key
	the key pressed
*/
/******************************************************************************/
void SceneBase::UpdateMovement(double dt)
{
	player.camera.Update(dt, TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, player.camera.getPosition().x/TERRAIN_SCALE.x, player.camera.getPosition().z/TERRAIN_SCALE.z));
}

/******************************************************************************/
/*!
\brief
Update Character

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateCharacters(double dt)
{
	TRS = player.getProperties();
	TRS.rotation.SetToRotation(player.camera.rotationY, 0, 1, 0);
	player.setTRS(TRS);
	player.setPosition(player.camera.getPosition());
	player.updateHitbox();
	ResetTRS(TRS);
}

/******************************************************************************/
/*!
\brief
Update Weapon

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateWeapons(double dt)
{
	if (player.getRender())
	{
		player.bagpack.currentWeapon->Update(dt);
	}

	for(std::vector<Character *>::iterator it = characterList.begin(); it != characterList.end(); ++it)
	{
		Character *go = (Character *)*it;
		if(go->getRender())
		{
			go->bagpack.currentWeapon->Update(dt);
		}
	}

	for(std::vector<Bullet *>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		Bullet *go = (Bullet *)*it;
		if(go->getRender())
		{
			go->Update(dt);
		}
	}
}

/******************************************************************************/
/*!
\brief
Update Variables

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateVariables(double dt)
{
	fps = (float)(1.f / dt);
}

/******************************************************************************/
/*!
\brief
Update collisions

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateCollisions(double dt)
{
	// check player with world bound
	if (player.camera.getPosition().x >= TERRAIN_SCALE.x * 0.45f || player.camera.getPosition().x <= -TERRAIN_SCALE.x * 0.45f
		|| player.camera.getPosition().z >= TERRAIN_SCALE.z * 0.45f || player.camera.getPosition().z <= -TERRAIN_SCALE.z * 0.45f)
	{
		player.camera.Reset();
	}

	if (player.camera.getPosition().x >= TERRAIN_SCALE.x * 0.35f || player.camera.getPosition().x <= -TERRAIN_SCALE.x * 0.35f
		|| player.camera.getPosition().z >= TERRAIN_SCALE.z * 0.35f || player.camera.getPosition().z <= -TERRAIN_SCALE.z * 0.35f)
	{
		leaving = true;
	}

	else
	{
		leaving = false;
	}

	for(std::vector<Bullet *>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		Bullet *go = (Bullet *)*it;
		if(go->getRender())
		{
			// check bullet with terrain
			if(go->getPosition().y < TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, go->getPosition().x/TERRAIN_SCALE.x, go->getPosition().z/TERRAIN_SCALE.z))
			{
				go->setRender(false);
				go->setStatus(false);
			}
		}

		for(std::vector<threeDObject *>::iterator it2 = environmentList.begin(); it2 != environmentList.end(); ++it2)
		{
			threeDObject *go2 = (threeDObject *)*it2;

			if(go2->getRender())
			{
				string boxName = "";

				if (check3DCollision(go->getHitBox(), go2->getHitBox(), boxName))
				{
					go->setRender(false);
					go->setStatus(false);
				}
			}
		}
	}

	// check player with environment obj
	for(std::vector<threeDObject *>::iterator it = environmentList.begin(); it != environmentList.end(); ++it)
	{
		threeDObject *go = (threeDObject *)*it;

		if(go->getRender())
		{
			string boxName = "";

			if (check3DCollision(player.getHitBox(), go->getHitBox(), boxName))
			{

			}
		}
	}
}

/******************************************************************************/
/*!
\brief
Update User Interface according to the scene

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateUI(double dt)
{
}

/******************************************************************************/
/*!
\brief
Update Sounds

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateSound(double dt)
{
}

/******************************************************************************/
/*!
\brief
Update camera status

\param key
	the key pressed
*/
/******************************************************************************/
void SceneBase::UpdateCameraStatus(const unsigned char key)
{
	player.camera.UpdateStatus(key);
}

/******************************************************************************/
/*!
\brief
Update weapon status

\param key
	the key pressed
*/
/******************************************************************************/
void SceneBase::UpdateWeaponStatus(const unsigned char key)
{
	static bool bSwitchWeapon = false;

	if (key == WA_FIRE)
	{
		if(player.bagpack.currentWeapon->Fire())
		{
			player.camera.setRecoiling(true);
			Bullet* firedBullet = fetchBullet();
			firedBullet->setPosition(player.camera.getTarget());
			firedBullet->setDir(player.camera.getView());
			firedBullet->setMesh(meshList[GEO_SPHERE]);
		}
	}

	else if (key == WA_RELOAD)
	{
		player.bagpack.currentWeapon->Reload();
	}

	else if (key == WA_CHANGEWEAPON && !bSwitchWeapon)
	{
		bSwitchWeapon = true;
		player.bagpack.switchWeapon(true);
	}

	else if(key == WA_NIL && bSwitchWeapon)
	{
		bSwitchWeapon = false;
	}
}