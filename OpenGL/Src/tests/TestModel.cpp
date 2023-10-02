#include "TestModel.h"
#include<time.h>
#include <filesystem>
test::TestModel::TestModel()
	: m_Shader(nullptr), m_Texture(nullptr), m_Translation(0, 0, 0), m_Scale(1, 1, 1),
	m_Rotation(0, 1, 0, 0), m_FoV(45)
{

	
	srand((unsigned int)time(0));


	m_Model = new Model("/res/models/backpack/backpack.obj");
	
	m_Texture = new Texture("res/models/backpack", "diffuse.jpg");

	/*m_plane = GameObject();
	Mesh tempPlane = Mesh();
	tempPlane.CreatePlane();
	m_plane.SetMesh(&tempPlane);*/

	m_Shader = new Shader("res/shaders/BasicModel.shader");

	m_Shader->Bind();
	//m_Shader->SetUniform1f("texture_diffuse1", 0);

}

test::TestModel::~TestModel()
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

	if (m_Model)
	{
		m_Model->Destroy();
		delete m_Model;
		m_Model = nullptr;
	}

}

void test::TestModel::OnUpdate(float dt)
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


	proj = cam.GetProj();
	view = cam.GetView();
}

void test::TestModel::OnRender()
{
	
	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLCall(glEnable(GL_DEPTH_TEST));
	glDepthFunc(GL_LESS);

	//m_Texture->Bind(0);

	{
		{

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

			glm::mat4 mvp = proj * view * model;

			m_Shader->Bind();

			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Shader->SetUniformMat4f("u_Model", model);
			//m_Shader->SetUniform1f("u_Time", glfwGetTime());
			m_Shader->SetUniform3f("u_LightColour", m_lightColour.r, m_lightColour.g, m_lightColour.b);
			m_Shader->SetUniform4f("u_AmbientColour", m_ambientColour.r,m_ambientColour.g,m_ambientColour.b,m_ambientStrength);
			m_Shader->SetUniform3f("u_LightPos", m_lightPos.x, m_lightPos.y, m_lightPos.z);
			m_Model->Draw(*m_Shader);
		}

	}
}

void test::TestModel::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	{
		ImGui::DragFloat("FoV", &m_FoV,0.5, 30, 180);
		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);
		ImGui::ColorEdit3("LightColour", &m_lightColour.x);
		ImGui::ColorEdit3("AmbientColour", &m_ambientColour.x);
		ImGui::DragFloat("AmbientStrength", &m_ambientStrength, 0.05f, 0, 1);

	}
}
