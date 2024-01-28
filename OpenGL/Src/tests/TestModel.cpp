#include "TestModel.h"
#include<time.h>
#include <filesystem>
#include<vector>
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

	cubeMesh.CreateCube();
	m_testCube = GameObject(row::vector3(0, 0, 0), glm::vec3(1, 1, 1), 10, row::vector3(0, 0, 0), glm::vec4(1, 1, 1, 1), "Cube");
	m_testCube.SetMesh(&cubeMesh);


	m_Shader = new Shader("res/shaders/BasicModel.shader");
	m_UnlitShader = new Shader("res/shaders/Basic.shader");
	m_UnlitShader->Bind();
	m_Shader->Bind();
	m_Texture->Bind(0);
	m_Shader->SetUniform1f("material.diffuse1", 0);
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
	Renderer renderer;

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

			m_light.Render(view, proj);
			m_Shader->Bind();

			m_Shader->SetUniformMat4f("u_Model", model);
			m_Shader->SetUniformMat4f("u_View", view);
			m_Shader->SetUniformMat4f("u_Projection", proj);
			//m_Shader->SetUniform1f("u_Time", glfwGetTime());
			//m_Shader->SetUniform3f("material.ambient", m_ambientColour.r, m_ambientColour.g, m_ambientColour.b);
			m_Shader->SetUniform3f("material.diffuse1", 1.0f, 0.5f, 0.31f);
			m_Shader->SetUniform3f("material.specular1", 0.5f, 0.5f, 0.5f);
			m_Shader->SetUniform1f("material.shininess", 32.0f);

			m_light.SetShaderUniform(m_Shader);

			//m_Shader->SetUniform3f("light.ambient", m_lightColour.r / 3, m_lightColour.g / 3, m_lightColour.b / 3);
			//m_Shader->SetUniform3f("light.diffuse", m_lightColour.r, m_lightColour.g, m_lightColour.b);
			//m_Shader->SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
			//m_Shader->SetUniform3f("light.position", m_lightPos.x, m_lightPos.y, m_lightPos.z);
			m_Model->Draw(*m_Shader);
			m_Shader->UnBind();

			//m_UnlitShader->Bind();
			//m_testCube.SetPosition(row::GlmToRow(m_lightPos));
			//m_testCube.BuildTransform();
			//mvp = proj * view * m_testCube.GetTransform();
			//m_UnlitShader->SetUniformMat4f("u_MVP", mvp);
			//m_UnlitShader->SetUniform4f("u_Colour", m_lightColour.r, m_lightColour.g, m_lightColour.b, 1);
			//m_testCube.Draw(*m_UnlitShader);
		}

	}
	
		/*std::vector<Mesh>::const_iterator meshIter;
		std::vector<Mesh>::const_iterator meshIterEnd;
		std::vector<Mesh> meshes = m_Model->GetMeshes();
		meshIter = meshes.begin();
		meshIterEnd = meshes.end();
		std::vector<Vertex>::iterator vertexIter;
		for (; meshIter != meshIterEnd; meshIter++)
		{
			Mesh curMesh = *meshIter;
			for (vertexIter = curMesh.m_Vertices.begin(); vertexIter != curMesh.m_Vertices.end(); vertexIter++)
			{
				m_UnlitShader->Bind();
				glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(0,0,0));
				glm::mat4 mvp = proj * view * model;
				m_UnlitShader->SetUniformMat4f("u_MVP", mvp);
				m_UnlitShader->SetUniform4f("u_Colour", 1, 1, 0, 1);
				renderer.DrawLine(*m_UnlitShader, vertexIter->Position, vertexIter->Position + vertexIter->Normal,glm::vec4(1,1,0,1));
				m_UnlitShader->UnBind();
			}
		}*/
	
}

void test::TestModel::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	{
		ImGui::DragFloat("FoV", &m_FoV,0.5, 30, 180);
		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);

		m_light.RenderImGUISettings();
	}
}
