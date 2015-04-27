/******************************************************************************/
/*!
\file	Update_Functions.cpp
\author Jun Xiang
\brief
Update all the scene stuff here
*/
/******************************************************************************/
#include "SceneBase.h"

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

\param dt
time passed since last update
*/
/******************************************************************************/
void SceneBase::UpdateCamera(double dt)
{
	camera.Update(dt, 0);
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