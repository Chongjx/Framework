/******************************************************************************/
/*!
\file	Render_Functions.cpp
\author Jun Xiang
\brief
Render all the scene stuff here
*/
/******************************************************************************/
#include "SceneBase.h"

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
	viewStack.LookAt(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
		camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
		camera.getUp().x, camera.getUp().y, camera.getUp().z);
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
	modelStack.Translate(0, 1800, 0);
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
	Render3DMesh(meshList[GEO_TERRAIN], false);
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

	/*for(std::vector<threeDObject *>::iterator it = threeDObjectList.begin(); it != threeDObjectList.end(); ++it)
	{
		threeDObject *go = (threeDObject *)*it;
		if(go->getRender())
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getPosition().x, go->getPosition().y, go->getPosition().z);
			modelStack.MultMatrix(go->getRotation());
			modelStack.Scale(go->getScale().x, go->getScale().y, go->getScale().z);
			Render3DMesh(go->getMesh(), go->getReflectLight());
			modelStack.PopMatrix();
		}
	}*/

	//// text
	//modelStack.PushMatrix();
	//modelStack.Scale(10, 10, 10);
	//RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	//modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
Render Characters and NPCs here
*/
/******************************************************************************/
void SceneBase::RenderCharacters(void)
{
}

/******************************************************************************/
/*!
\brief
Render Bullet here
*/
/******************************************************************************/
void SceneBase::RenderBullets(void)
{
	for(int i = 0; i < pistol.m_Ammo.size(); ++i)
	{
		if (pistol.m_Ammo[i]->getStatus() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(pistol.m_Ammo[i]->getPosition().x, pistol.m_Ammo[i]->getPosition().y, pistol.m_Ammo[i]->getPosition().z);
			Render3DMesh(pistol.getMesh(), pistol.getReflectLight());
			modelStack.PopMatrix();
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

	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);

	std::ostringstream ss1;
	ss1.precision(4);
	ss1 << "Light(" << lights[0].position.x << ", " << lights[0].position.y << ", " << lights[0].position.z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 0, 3);

	RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);

	Render2DMesh(m_Minimap->GetBackground(), false, 20.f, 55, 45);
	Render2DMesh(m_Minimap->GetBorder(), false, 20.f, 55, 45);
	Render2DMesh(m_Minimap->GetAvatar(), false, 10.f, 55, 45);

	SetHUD(false);
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
		glUniform1f(m_parameters[U_FOG_ENABLED], 1);
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
void SceneBase::Render2DMesh(Mesh* mesh, bool enableLight, float size, float x, float y)
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