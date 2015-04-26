#include "SceneText.h"

void SceneText::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
						camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
						camera.getUp().x, camera.getUp().y, camera.getUp().z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	if(lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}
	
	Render3DMesh(meshList[GEO_AXES], false);
	
	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	Render3DMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	RenderEnvironment();

	// perspective;
	////perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	//projectionStack.LoadMatrix(perspective);
	//viewStack.LoadIdentity();
	//
	//modelStack.PushMatrix();
	////modelStack.Translate(20, 0, -20);
	////modelStack.Scale(0.1f, 0.1f, 0.1f);
	//modelStack.Scale(50, 50, 50);
	////Render3DMesh(meshList[GEO_QUAD], false);
	//RenderText(meshList[GEO_TEXT], "HelloWorld", Color(0, 1, 0));
	//modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-20, 0, -20);
	Render3DMesh(meshList[GEO_OBJECT], false);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(20, 0, -20);
	Render3DMesh(meshList[GEO_OBJECT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	//RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	modelStack.PopMatrix();

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);
	
	std::ostringstream ss1;
	ss1.precision(4);
	ss1 << "Light(" << lights[0].position.x << ", " << lights[0].position.y << ", " << lights[0].position.z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 0, 3);

	RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);
}

/******************************************************************************/
/*!
\brief
render a map
*/
/******************************************************************************/
void SceneText::RenderMiniMap()
{
	//glDisable(GL_DEPTH_TEST);

	/*if(currentScene != SCENE_MENU)
	{
		static int width, height;

		glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

		Mtx44 projection;
		projection.SetToOrtho(-width/15, width/15, -height/15, height/15, -10, 800);
		projectionStack.LoadMatrix(projection);

		viewStack.LoadIdentity();
		viewStack.LookAt(topdownCam.position.x, topdownCam.position.y, topdownCam.position.z, topdownCam.target.x, topdownCam.target.y, topdownCam.target.z, topdownCam.up.x, topdownCam.up.y, topdownCam.up.z);

		RenderLights();
		RenderBullet(); 
        RenderEnvironment();
		RenderCharacters();
		RenderPlayer();
		RenderMarketStuff();
	}*/
}