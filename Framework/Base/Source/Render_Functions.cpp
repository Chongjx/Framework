/******************************************************************************/
/*!
\file	Render_Functions.cpp
\author Jun Xiang
\brief
Render all the scene stuff here
*/
/******************************************************************************/
#include "SceneBase.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Setting the camera
*/
/******************************************************************************/
void SceneBase::SetCamera(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(perspective);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(player.camera.getPosition().x, player.camera.getPosition().y, player.camera.getPosition().z,
		player.camera.getTarget().x, player.camera.getTarget().y, player.camera.getTarget().z,
		player.camera.getUp().x, player.camera.getUp().y, player.camera.getUp().z);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
}

/******************************************************************************/
/*!
\brief
Render Lights
*/
/******************************************************************************/
void SceneBase::RenderLights(void)
{
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		if(lights[i].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[i].position.x, lights[i].position.y, lights[i].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[i * 11 + 12], 1, &lightDirection_cameraspace.x);
		}
		else if(lights[i].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[i].position;
			glUniform3fv(m_parameters[i * 11 + 12], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[i].spotDirection;
			glUniform3fv(m_parameters[i * 11 + 8], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[i].position;
			glUniform3fv(m_parameters[i * 11 + 12], 1, &lightPosition_cameraspace.x);
		}
	}

	for (int i = 0; i < NUM_LIGHTS; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(lights[i].position.x, lights[i].position.y, lights[i].position.z);
		Render3DMesh(meshList[GEO_LIGHTBALL], false);
		modelStack.PopMatrix();
	}
}

/******************************************************************************/
/*!
\brief
Render Sky plane here
*/
/******************************************************************************/
void SceneBase::RenderSkyPlane(void)
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 2000, 0);
	Render3DMesh(meshList[GEO_SKYPLANE], false);
	modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
Render Terrain here
*/
/******************************************************************************/
void SceneBase::RenderTerrain(void)
{
	modelStack.PushMatrix();
	modelStack.Scale(TERRAIN_SCALE.x, TERRAIN_SCALE.y, TERRAIN_SCALE.z);
	Render3DMesh(meshList[GEO_TERRAIN], true);
	modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
Render Environment objects here
*/
/******************************************************************************/
void SceneBase::RenderEnvironment(void)
{
	// axis
	Render3DMesh(meshList[GEO_AXES], false);

	RenderSkyPlane();
	RenderTerrain();

	for(std::vector<threeDObject *>::iterator it = environmentList.begin(); it != environmentList.end(); ++it)
	{
		threeDObject *go = (threeDObject *)*it;
		if(go->getRender())
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getProperties().translation);
			modelStack.MultMatrix(go->getProperties().rotation);
			modelStack.Scale(go->getProperties().scale);
			Render3DMesh(go->getMesh(), go->getReflectLight());
			modelStack.PopMatrix();

			if (bDebugMode)
			{
				modelStack.PushMatrix();	
				modelStack.Translate(go->getHitBox().getMidPoint().x, go->getHitBox().getMidPoint().y, go->getHitBox().getMidPoint().z);
				modelStack.MultMatrix(go->getProperties().rotation);
				modelStack.Scale(go->getHitBox().getLength(), go->getHitBox().getHeight(), go->getHitBox().getDepth());
				Render3DMesh(meshList[GEO_DEBUG], false);
				modelStack.PopMatrix();
			}
		}
	}
}

/******************************************************************************/
/*!
\brief
Render Characters and NPCs here
*/
/******************************************************************************/
void SceneBase::RenderCharacters(void)
{
	modelStack.PushMatrix();
	modelStack.Translate(player.getProperties().translation);
	modelStack.MultMatrix(player.getProperties().rotation);
	modelStack.Scale(player.getProperties().scale);
	//Render3DMesh(player.getMesh(), player.getReflectLight());
	modelStack.PushMatrix();
	if (player.bagpack.currentWeapon->getReload())
	{
		modelStack.Rotate(player.camera.rotationX + 15, 1, 0, 0);
	}
	else
	{
		modelStack.Rotate(player.camera.rotationX, 1, 0, 0);
	}
	modelStack.Translate(player.bagpack.currentWeapon->getProperties().translation);
	modelStack.MultMatrix(player.bagpack.currentWeapon->getProperties().rotation);
	modelStack.Scale((player.bagpack.currentWeapon)->getProperties().scale);
	Render3DMesh((player.bagpack.currentWeapon)->getMesh(), (player.bagpack.currentWeapon)->getReflectLight());

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if(bDebugMode)
	{
		modelStack.PushMatrix();
		modelStack.Translate(player.getHitBox().getMidPoint().x, player.getHitBox().getMidPoint().y, player.getHitBox().getMidPoint().z);
		modelStack.MultMatrix(player.getProperties().rotation);
		modelStack.Scale(player.getProperties().scale);
		Render3DMesh(meshList[GEO_DEBUG], false);
		modelStack.PopMatrix();
	}

	for(std::vector<Character *>::iterator it = characterList.begin(); it != characterList.end(); ++it)
	{
		Character *go = (Character *)*it;
		if(go->getRender())
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getProperties().translation);
			modelStack.MultMatrix(go->getProperties().rotation);
			modelStack.Scale(go->getProperties().scale);
			Render3DMesh(go->getMesh(), go->getReflectLight());
			modelStack.PopMatrix();

			if(bDebugMode)
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->getHitBox().getMidPoint().x,go->getHitBox().getMidPoint().y, go->getHitBox().getMidPoint().z);
				modelStack.MultMatrix(go->getProperties().rotation);
				modelStack.Scale(go->getHitBox().getLength(), go->getHitBox().getHeight(), go->getHitBox().getDepth());
				Render3DMesh(meshList[GEO_DEBUG], false);
				modelStack.PopMatrix();
			}
		}
	}
}

/******************************************************************************/
/*!
\brief
Render Bullet here
*/
/******************************************************************************/
void SceneBase::RenderBullets(void)
{
	for(std::vector<Bullet *>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		Bullet *go = (Bullet *)*it;
		if(go->getRender())
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getProperties().translation);
			modelStack.MultMatrix(go->getProperties().rotation);
			modelStack.Scale(go->getProperties().scale);
			Render3DMesh(meshList[GEO_SPHERE], go->getReflectLight());
			modelStack.PopMatrix();

			if (bDebugMode)
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->getHitBox().getMidPoint().x, go->getHitBox().getMidPoint().y, go->getHitBox().getMidPoint().z);
				modelStack.MultMatrix(go->getProperties().rotation);
				modelStack.Scale(go->getHitBox().getLength(), go->getHitBox().getHeight(), go->getHitBox().getDepth());
				Render3DMesh(meshList[GEO_DEBUG], false);
				modelStack.PopMatrix();
			}
		}
	}
}

/******************************************************************************/
/*!
\brief
Render UI and HUD here
*/
/******************************************************************************/
void SceneBase::RenderUI(void)
{
	//On screen text
	SetHUD(true);

	Color textColor(47.f / 255.f, 144.f / 255.f, 38.f/ 255.f);

	std::ostringstream ss;
	ss.precision(4);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), textColor, FONT_SIZE, 0, 57);

	if (timer <= startTimer)
	{
		std::ostringstream startDisplay;
		startDisplay << "Survive";
		RenderTextOnScreen(meshList[GEO_TEXT], startDisplay.str(), textColor, FONT_SIZE, 30, 30);
	}

	else
	{
		std::ostringstream waveCount;
		waveCount << "Wave:" << wave;
		RenderTextOnScreen(meshList[GEO_TEXT], waveCount.str(), textColor, FONT_SIZE, 35, 57);
	}

	Render2DMesh(meshList[GEO_HEALTHBAR], false, 34.f, 63.5f, 45.f);

	std::ostringstream health;
	health << player.m_iHealth;
	RenderTextOnScreen(meshList[GEO_TEXT], health.str(), Color(1, 0, 0), FONT_SIZE, 70.f, 54.f);

	// ammo clip
	std::ostringstream ss1;
	ss1.precision(4);
	ss1 << player.bagpack.currentWeapon->getName();
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 0, 1), FONT_SIZE * 0.485f, 69.f, 51.f);

	std::ostringstream ss2;
	ss2 << "Mag:" << player.bagpack.currentWeapon->getMagazineAmmo();
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 0, 1), FONT_SIZE * 0.485f, 69.f, 48.f);

	std::ostringstream ss3;
	ss3 << "Ammo:" << player.bagpack.currentWeapon->getAmmo();
	RenderTextOnScreen(meshList[GEO_TEXT], ss3.str(), Color(0, 0, 1), FONT_SIZE * 0.485f, 69.f, 45.f);

	if (!gameOver)
	{
		if (timer >= startTimer)
		{
			switch(player.bagpack.currentWeapon->getWeaponType())
			{
			case WEAP_PISTOL:
				{
					Render2DMesh(meshList[GEO_PISTOLCH], false, 10.f, 0, 0);
					break;
				}
			case WEAP_RIFLE:
				{
					Render2DMesh(meshList[GEO_RIFLECH], false, 10.f, 0, 0);
					break;
				}
			case WEAP_SNIPER:
				{
					Render2DMesh(meshList[GEO_SNIPERCH], false, 10.f, 0, 0);
					break;
				}
			}
		}

		if(leaving)
		{
			Render2DMesh(meshList[GEO_QUAD], false, 70.f, 0, 0);
			std::ostringstream ss4;
			ss4 << "WARINING: LEAVING ZONE";
			RenderTextOnScreen(meshList[GEO_TEXT], ss4.str(), Color(1, 1, 1), FONT_SIZE * 0.5f, 24, 30);
		}
	}

	else
	{
		Render2DMesh(meshList[GEO_QUAD], false, 200.f, 0, 0);

		std::ostringstream ss5;
		ss5 << "Game Over" << std::endl;
		RenderTextOnScreen(meshList[GEO_TEXT], ss5.str(), Color(1, 1, 1), FONT_SIZE, 25.f, 45.f);

		std::ostringstream ss6;
		ss6 << "Wave survived: " << wave;
		RenderTextOnScreen(meshList[GEO_TEXT], ss6.str(), Color(1, 1, 1), FONT_SIZE, 15.f, 40.f);


		std::ostringstream ss7;
		ss7 <<"Left click to replay" << std::endl;
		RenderTextOnScreen(meshList[GEO_TEXT], ss7.str(), Color(1, 1, 1), FONT_SIZE, 5.f, 30.f);
	}

	RenderMiniMap();

	SetHUD(false);
}

/******************************************************************************/
/*!
\brief
Render minimap
*/
/******************************************************************************/
void SceneBase::RenderMiniMap(void)
{
	// minimap
	modelStack.PushMatrix();
	modelStack.Translate(-60, -40, 0);
	//modelStack.Scale(1.f, 1.f, 1);
	// border
	modelStack.PushMatrix();
	modelStack.Scale(7, 7, 1);
	Render2DMesh(m_Minimap->getBorder(), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(m_Minimap->player.getAngle(), 0, 0, 1);

	// background (radar)
	modelStack.PushMatrix();
	modelStack.Scale(20, 20, 1);
	Render2DMesh(m_Minimap->getBackground(), false);
	modelStack.PopMatrix();

	// enemy
	for(int i = 0; i < m_Minimap->enemyList.size(); ++i)
	{
		if (m_Minimap->enemyList[i].getRender())
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_Minimap->enemyList[i].getPosition_x(), m_Minimap->enemyList[i].getPosition_y(), 0);
			Render2DMesh(m_Minimap->enemyList[i].getAvatar(), false);
			modelStack.PopMatrix();
		}
	}

	// environment
	for(int i = 0; i < m_Minimap->statictList.size(); ++i)
	{
		if (m_Minimap->statictList[i].getRender())
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_Minimap->statictList[i].getPosition_x(), m_Minimap->statictList[i].getPosition_y(), 0);
			modelStack.Scale(3.f, 3.f, 3.f);
			Render2DMesh(m_Minimap->statictList[i].getAvatar(), false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();

	// player avatar
	Render2DMesh(m_Minimap->player.getAvatar(), false);
	modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
RenderHUD
*/
/******************************************************************************/
void SceneBase::SetHUD(const bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glDisable (GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		glUniform1f(m_parameters[U_FOG_ENABLED], 0);
	}

	else
	{
		projectionStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		glUniform1f(m_parameters[U_FOG_ENABLED], bFogEnabled);
	}
}

/******************************************************************************/
/*!
\brief
Render 3D mesh function
*/
/******************************************************************************/
void SceneBase::Render3DMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}

	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	for (unsigned i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if(mesh->textureID[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED + (i * 2)], 1);

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureID[i]);
			glUniform1i(m_parameters[U_COLOR0_TEXTURE + (i * 2)], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED + (i * 2)], 0);
		}
	}
	mesh->Render();

	for (unsigned i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if(mesh->textureID[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

/******************************************************************************/
/*!
\brief
Render 2D mesh on screen function
*/
/******************************************************************************/
void SceneBase::Render2DMesh(Mesh* mesh, bool enableLight, float size, float x, float y, float rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60 , -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(rotate, 0, 0, 1);
	modelStack.Scale(size, size, size);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, & MVP.a[0]);

	for (unsigned i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if(mesh->textureID[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED + (i * 2)], 1);

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureID[i]);
			glUniform1i(m_parameters[U_COLOR0_TEXTURE + (i * 2)], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED + (i * 2)], 0);
		}
	}
	mesh->Render();

	for (unsigned i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if(mesh->textureID[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
Render 2D mesh function which allows hir
*/
/******************************************************************************/
void SceneBase::Render2DMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60 , -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	for (unsigned i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if(mesh->textureID[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED + (i * 2)], 1);

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureID[i]);
			glUniform1i(m_parameters[U_COLOR0_TEXTURE + (i * 2)], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED + (i * 2)], 0);
		}
	}
	mesh->Render();

	for (unsigned i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if(mesh->textureID[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

/******************************************************************************/
/*!
\brief
Render Text in world space function
*/
/******************************************************************************/
void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID[0]);
	glUniform1i(m_parameters[U_COLOR0_TEXTURE], 0);

	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

/******************************************************************************/
/*!
\brief
Render Text on screen function
*/
/******************************************************************************/
void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR0_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID[0]);
	glUniform1i(m_parameters[U_COLOR0_TEXTURE], 0);

	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}