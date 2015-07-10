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

	if (player.m_iHealth <= 0)
	{
		player.m_iHealth = 0;
		gameOver = true;
	}

	// update more enemies if wave clear

	if (timer >= startTimer)
	{
		if(enemyCount == 0)
		{
			wave += 1;
			maxEnemy = wave * 3;

			for(unsigned i = enemyCount; i < maxEnemy; ++i)
			{
				float xCoord = Math::RandFloatMinMax(-TERRAIN_SCALE.x * 0.5f, TERRAIN_SCALE.x * 0.5f);
				float zCoord = Math::RandFloatMinMax(-TERRAIN_SCALE.z * 0.5f, TERRAIN_SCALE.z * 0.5f);
				Character* alien = fetchCharacter();
				alien->setMesh(meshList[GEO_ALIEN]);
				alien->setHitBox(threeDhitbox(Vector3(0, 0, 0), 13.8f, 27.8f, 19.f, "alien"));
				alien->setPosition(Vector3(xCoord, TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, xCoord/TERRAIN_SCALE.x, zCoord/TERRAIN_SCALE.z) - 5.f, zCoord));
				alien->enemyTarget = &player;
				alien->m_iHealth = 10 * wave;
				alien->m_iID = 1;
				alien->camera.Init(alien->getPosition(), player.getPosition(), Vector3(0, 1, 0));

				++enemyCount;

				newAvatar.setAvatar(MeshBuilder::GenerateQuad("MinimapAvatar", Color(1, 1, 1), 1.f));
				newAvatar.setPosition(alien->getPosition().x / TERRAIN_SCALE.x * MINIMAP_SCALE, alien->getPosition().z / TERRAIN_SCALE.z * MINIMAP_SCALE);
				newAvatar.getAvatar()->textureID[0] = LoadTGA("Image//enemyAvatar.tga");
				m_Minimap->enemyList.push_back(newAvatar);
			}
		}

		for(std::vector<Character *>::iterator it = characterList.begin(); it != characterList.end(); ++it)
		{
			Character *go = (Character *)*it;
			if(go->getRender())
			{
				// chase after target
				TRS = go->getProperties();
				float theta = Math::RadianToDegree(atan2(go->camera.getView().x, go->camera.getView().z));
				TRS.rotation.SetToRotation(theta, 0, 1, 0);
				go->setTRS(TRS);
				if (go->camera.getTarget() != go->camera.getPosition())
				{
					go->camera.moveForward(dt, TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, go->camera.getPosition().x/TERRAIN_SCALE.x, go->camera.getPosition().z/TERRAIN_SCALE.z) - 5.f);
				}
				go->camera.setTarget(player.getPosition());
				go->setPosition(go->camera.getPosition());

				go->updateHitbox();

				if(go->m_iHealth <= 0)
				{
					go->setRender(false);

					int dropBonus = Math::RandIntMinMax(1, 3);

					if (dropBonus == 3)
					{
						itemBonus = Math::RandIntMinMax(1, 3);

						// increase pistol ammo
						if (itemBonus == 1)
						{
							player.bagpack.pistol.setAmmo(player.bagpack.pistol.getAmmo() + 30);
						}

						// increase rifle ammo
						else if (itemBonus == 2)
						{
							player.bagpack.rifle.setAmmo(player.bagpack.rifle.getAmmo() + 30);
						}

						else if(player.m_iHealth < 100)
						{
							// increase health by 30 if health less than 70
							if (player.m_iHealth < 70)
							{
								player.m_iHealth += 10;
							}

							// recover health to full health
							else
							{
								player.m_iHealth = 100;
							}
						}

						UpdateSoundStatus('p');
					}

					else
					{
						itemBonus = 0;
					}

					//remove enemy from minimap
					int pos = it - characterList.begin();

					m_Minimap->enemyList[pos].setRender(false);

					--enemyCount;
				}
			}
		}
	}
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

	timer += (float)dt;

	if (timer > 0)
	{
		Particle* smoke = fetchParticle();
		smoke->setGravity(false);
		smoke->setPosition(Vector3(0, 100, 205));
		smoke->setVelocity(Vector3(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(50, 100), Math::RandFloatMinMax(-10, 10)));
	}

	for(std::vector<Particle *>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		Particle *go = (Particle *)*it;
		if(go->getRender())
		{
			// if this particle is affected by gravity
			if (go->getGravity())
			{
				go->setVelocity(go->getVelocity() + GRAVITY * dt);
				go->setPosition(go->getPosition() + go->getVelocity() * (float)dt);
			}

			else
			{
				TRS = go->getProperties();
				TRS.scale.SetToScale(Vector3(TRS.scale.a[0] + 5 * dt, TRS.scale.a[5] + 5 * dt, TRS.scale.a[10] + 5 * dt));
				go->setTRS(TRS);
				go->setPosition(go->getPosition() + go->getVelocity() * (float)dt);
			}

			if (go->getPosition().y > 500)
			{
				go->setRender(false);
			}
		}
	}

	for(std::vector<GameObject *>::iterator it = billboardList.begin(); it != billboardList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		// sort the billboard
		for (int iter = 1; iter < billboardList.size(); ++iter)
		{
			for (int index = 0; index < billboardList.size() - iter; ++index)
			{
				float dist1 = (billboardList[index]->getPosition() - player.camera.getPosition()).Length();
				float dist2 = (billboardList[index + 1]->getPosition() - player.camera.getPosition()).Length();
				if (dist1 < dist2)
				{
					// swap billboard if dist is larger
					GameObject* temp = billboardList[index];
					billboardList[index] = billboardList[index + 1];
					billboardList[index + 1] = temp;
				}
			}
		}

		// update rotation
		TRS = go->getProperties();
		Vector3 dir = (go->getPosition() - player.camera.getPosition()).Normalized();
		float theta = Math::RadianToDegree(atan2(dir.x, dir.z)) + 180.f;
		TRS.rotation.SetToRotation(theta, 0, 1, 0);
		go->setTRS(TRS);
	}
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

	// check player with environment
	/*for(std::vector<threeDObject *>::iterator it = environmentList.begin(); it != environmentList.end(); ++it)
	{
	threeDObject *go = (threeDObject *)*it;
	if(go->getRender())
	{
	string boxName = "";
	if (check3DCollision(player.getHitBox(), go->getHitBox(), boxName))
	{
	if(player.getPosition().z < go->getPosition().z)
	{
	player.camera.moveBackward(dt, TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, player.camera.getPosition().x/TERRAIN_SCALE.x, player.camera.getPosition().z/TERRAIN_SCALE.z));
	}

	else
	{
	player.camera.moveForward(dt, TERRAIN_SCALE.y * ReadHeightMap(m_heightMap, player.camera.getPosition().x/TERRAIN_SCALE.x, player.camera.getPosition().z/TERRAIN_SCALE.z));
	}
	}
	}
	}*/

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
				break;
			}

			// check with environment obj
			for(std::vector<threeDObject *>::iterator it2 = environmentList.begin(); it2 != environmentList.end(); ++it2)
			{
				threeDObject *go2 = (threeDObject *)*it2;

				if(go2->getRender())
				{
					if ((go->getHitBox().getMidPoint() - go2->getHitBox().getMidPoint()).Length() <= 30.f)
					{
						string boxName = "";
						if (check3DCollision(go->getHitBox(), go2->getHitBox(), boxName))
						{
							go->setRender(false);
							go->setStatus(false);
							break;
						}
					}
				}
			}

			// check with aliens
			for(std::vector<Character *>::iterator it2 = characterList.begin(); it2 != characterList.end(); ++it2)
			{
				Character *go2 = (Character *)*it2;

				if(go2->getRender())
				{
					if ((go->getHitBox().getMidPoint() - go2->getHitBox().getMidPoint()).Length() <= 30.f)
					{
						string boxName = "";
						if (check3DCollision(go->getHitBox(), go2->getHitBox(), boxName))
						{
							go->setRender(false);
							go->setStatus(false);
							go2->m_iHealth -= player.bagpack.currentWeapon->getDmg();
							break;
						}
					}
				}
			}
		}
	}

	//check aliens with aliens
	for(std::vector<Character *>::iterator it = characterList.begin(); it != characterList.end(); ++it)
	{
		Character *go = (Character *)*it;
		if(go->getRender())
		{
			for(std::vector<Character *>::iterator it2 = it + 1; it2 != characterList.end(); ++it2)
			{
				Character *go2 = (Character *)*it2;
				if (go2->getRender())
				{
					if ((go->getPosition() - go2->getPosition()).Length() < go->getHitBox().getLength() * 2)
					{
						Vector3 firstDir = (go->getPosition() - go2->getPosition()).Normalized();
						float dist = (go->getPosition() - go2->getPosition()).Length();

						go->camera.setTarget(go->camera.getTarget() + firstDir * (1.f / dist) * REPULSE_FORCE * dt);
						go2->camera.setTarget(go2->camera.getTarget() + (-firstDir) * (1.f / dist) * REPULSE_FORCE * dt);
					}
				}
			}
		}
	}

	//check player with aliens
	for(std::vector<Character *>::iterator it = characterList.begin(); it != characterList.end(); ++it)
	{
		Character *go = (Character *)*it;
		if(go->getRender())
		{
			if ((go->getHitBox().getMidPoint() - player.getHitBox().getMidPoint()).Length() <= 30.f)
			{
				UpdateSoundStatus('m');
				string boxName = "";
				if (check3DCollision(player.getHitBox(), go->getHitBox(), boxName))
				{
					player.m_iHealth -= 1;
					UpdateCameraStatus(32);
					UpdateSoundStatus('0');
					break;
				}
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
	// character avatar
	m_Minimap->player.setPosition(-player.getPosition().x / TERRAIN_SCALE.x * MINIMAP_SCALE, player.getPosition().z / TERRAIN_SCALE.z * MINIMAP_SCALE);

	m_Minimap->player.setAngle(-player.camera.rotationY);

	// render environment object
	for(int i = 0; i < environmentList.size(); ++i)
	{
		if(environmentList[i]->getRender())
		{
			if ((environmentList[i]->getPosition() - player.getPosition()).Length() < 500.f)
			{
				m_Minimap->statictList[i].setRender(true);
				m_Minimap->statictList[i].setPosition(-environmentList[i]->getPosition().x / TERRAIN_SCALE.x * MINIMAP_SCALE - m_Minimap->player.getPosition_x(), environmentList[i]->getPosition().z / TERRAIN_SCALE.z * MINIMAP_SCALE - m_Minimap->player.getPosition_y()); 
			}

			else
			{
				m_Minimap->statictList[i].setRender(false);
			}
		}
	}

	for(int i = 0; i < characterList.size(); ++i)
	{
		if(characterList[i]->getRender())
		{
			if ((characterList[i]->getPosition() - player.getPosition()).Length() < 500.f)
			{
				m_Minimap->enemyList[i].setRender(true);
				m_Minimap->enemyList[i].setPosition(-characterList[i]->getPosition().x / TERRAIN_SCALE.x * MINIMAP_SCALE - m_Minimap->player.getPosition_x(), characterList[i]->getPosition().z / TERRAIN_SCALE.z * MINIMAP_SCALE- m_Minimap->player.getPosition_y());  
			}

			else
			{
				m_Minimap->enemyList[i].setRender(false);
			}
		}
	}
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
	if (timer >= startTimer)
	{
		player.camera.UpdateStatus(key);
	}
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

	if (timer >= startTimer)
	{
		if (key == WA_FIRE)
		{
			if(player.bagpack.currentWeapon->Fire())
			{
				player.camera.setRecoiling(true);
				Bullet* firedBullet = fetchBullet();
				firedBullet->setPosition(player.camera.getTarget());
				firedBullet->setDir(player.camera.getView());

				UpdateSoundStatus('1');
			}
		}

		else if (key == WA_RELOAD)
		{
			if(player.bagpack.currentWeapon->Reload())
			{
				UpdateSoundStatus('2');
			}
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
}

/******************************************************************************/
/*!
\brief
Update Sounds

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateSoundStatus(const unsigned char key)
{
	static bool shootsound = true;
	static bool reload = true;
	static bool pickup = true;
	static bool attacked = true;

	engine->setListenerPosition(vec3df(player.camera.getPosition().x, player.camera.getPosition().y, player.camera.getPosition().z),vec3df(player.camera.getView().x, player.camera.getView().y, player.camera.getView().z));

	switch(player.bagpack.currentWeapon->getWeaponType())
	{
	case WEAP_PISTOL:
		{
			if (key == '1' && shootsound)
			{
				snd[FIREPISTOL] = engine->play2D("Wav//pistol.wav");
				shootsound = false;
			}

			else if (key != '1')
			{
				shootsound = true;
			}

			if (key == '2' && reload)
			{
				snd[FIREPISTOL] = engine->play2D("Wav//pistolreload.wav");
				reload = false;
			}

			else if (key != '2')
			{
				reload = true;
			}

			break;
		}
	case WEAP_RIFLE:
		{
			if (key == '1' && shootsound)
			{
				snd[FIRERIFLE] = engine->play2D("Wav//rifle.wav");
				shootsound = false;
			}

			else if (key != '1')
			{
				shootsound = true;
			}

			if (key == '2' && reload)
			{
				snd[FIREPISTOL] = engine->play2D("Wav//riflereload.wav");
				reload = false;
			}

			else if (key != '2')
			{
				reload = true;
			}
			break;
		}
	}

	if(key == 'p' && pickup)
	{
		snd[FIREPISTOL] = engine->play2D("Wav//bonus.ogg");
		pickup = false;
	}

	else if (key != 'p')
	{
		pickup = true;
	}

	//if (key == '0' && attacked)
	//{	
	//	snd[ATTACKED] = engine->play2D("Wav//attacked.wav");
	//	attacked = false;
	//}

	//else if (key != '0')
	//{
	//	attacked = true;
	//}
}