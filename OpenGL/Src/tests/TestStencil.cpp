#include "TestStencil.h"
#include<time.h>
test::TestStencil::TestStencil()
	: m_Shader(nullptr), m_Texture(nullptr), m_Translation(0, 0, 0), m_Scale(1, 1, 1),
	m_Rotation(0, 1, 0, 0), m_FoV(45),m_CameraControl(true)
{

	
	srand(time(0));



	cubeMesh.CreateCube();
	
	for (int o = 0; o < 6; o++)
	{
		float x, y, z;
		float i, j, k;

		x = (float)(rand() % 100 - 50) / 10.f;
		y = (float)(rand() % 100 - 50) / 10.f;
		z = (float)(rand() % 100 - 50) / 10.f;

		i = (float)(rand() % 200 - 100) / 100.f;
		j = (float)(rand() % 200 - 100) / 100.f;
		k = (float)(rand() % 200 - 100) / 100.f;

		GameObject* object = new GameObject(row::vector3(x,y,z),glm::vec3(1,1,1),1,row::vector3(0,0,0),glm::vec4(i,j,k,1),"Oof");
		object->SetRotation(glm::vec4(i, j, k, 1));
		object->SetMesh(&cubeMesh);
		object->BuildTransform();
		cubes.push_back(object);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);




	m_Shader = new Shader("res/shaders/Basic.shader");
	m_StencilShader = new Shader("res/shaders/OutlineStencil.shader");
}

test::TestStencil::~TestStencil()
{
	if (m_Shader)
	{
		delete m_Shader;
		m_Shader = nullptr;
	}

	if (m_StencilShader)
	{
		delete m_StencilShader;
		m_StencilShader = nullptr;
	}

	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}

	for (int i = 0; i < 6; i++)
	{
		if (cubes[i])
		{
			delete cubes[i];
		}
	}

}

void test::TestStencil::OnUpdate(float dt)
{

	if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) 
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		cam.UpdateOrientation(dt, m_Window);
	}
	else
	{
		double xPos, yPos;
		glfwGetCursorPos(m_Window, &xPos, &yPos);
		cam.SetMouseOrigin(glm::vec2(xPos, yPos));
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	cam.SetFoV(m_FoV);
	cam.UpdatePosition(dt, m_Window);
	cam.UpdateMatrices(dt);


	for (int i = 0; i < 6; i++)
	{
		cubes[i]->BuildTransform();
	}

	proj = cam.GetProj();
	view = cam.GetView();
}

void test::TestStencil::OnRender()
{

	Renderer renderer;


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLCall(glEnable(GL_DEPTH_TEST));
	glDepthFunc(GL_LESS);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	// Accept fragment if it closer to the camera than the former one


	glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should pass the stencil test
	glStencilMask(0xFF); // enable writing to the stencil buffer

	{
		for (int i = 0; i < 6; i++)
		{
			cubes[i]->SetScale(glm::vec3(1, 1, 1));
			cubes[i]->BuildTransform();

			glm::mat4 model = cubes[i]->GetTransform();
			glm::mat4 mvp = proj * view * model;
			glm::vec4 colour = cubes[i]->GetColour();

			m_Shader->Bind();
			m_Shader->SetUniform4f("u_Colour", colour.x, colour.y, colour.z, 1.0);

			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*cubes[i]->GetMesh()->GetVAO(), *cubes[i]->GetMesh()->GetIB(), *m_Shader);
		}


		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00); // disable writing to the stencil buffer
		glDisable(GL_DEPTH_TEST);

		for (int i = 0; i < 6; i++)
		{
			cubes[i]->SetScale(glm::vec3(1.1, 1.1, 1.1));
			cubes[i]->BuildTransform();

			glm::mat4 model = cubes[i]->GetTransform();
			glm::mat4 mvp = proj * view * model;

			//m_Shader->SetUniform4f("u_Colour", colour.x, colour.y, colour.z, 1.0);


			m_StencilShader->Bind();
			m_StencilShader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*cubes[i]->GetMesh()->GetVAO(), *cubes[i]->GetMesh()->GetIB(), *m_StencilShader);

		}

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glEnable(GL_DEPTH_TEST);

	}
}

void test::TestStencil::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	{
		ImGui::DragFloat("FoV", &m_FoV,0.5, 30, 180);
		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);
	}
}
