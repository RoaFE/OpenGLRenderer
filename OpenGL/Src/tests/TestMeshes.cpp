#include "TestMeshes.h"

test::TestMeshes::TestMeshes()
	: m_FoV(45)
	, m_Speed(3)
	, m_ClearColour{ 0.025f,0.0615f,0.15f,1.0f }
	, wireFrame(false)
{
	cubeMesh.CreateCube();
	sphereMesh.CreateSphere(1,20,20);

	m_Mesh1.SetMesh(&cubeMesh);
	m_Mesh2.SetMesh(&sphereMesh);
	m_Mesh1.SetPosition(row::vector3(0, 1, 0));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();

	m_Shader->SetUniform4f("u_Colour", 0.8f, 0.3f, 0.4f, 1.0f);



	m_Texture = new Texture("res/textures","Oh.png");
	m_Shader->SetUniform1i("u_Texture", 0);

	cam.SetPos(0, 0, 30);
}

test::TestMeshes::~TestMeshes()
{

	if (m_Shader)
	{
		delete m_Shader;
		m_Shader = nullptr;
	}


	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
}

void test::TestMeshes::OnUpdate(float dt)
{
	if (wireFrame)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
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


	m_Mesh1.BuildTransform();
	m_Mesh2.BuildTransform();
	proj = cam.GetProj();
	view = cam.GetView();
}

void test::TestMeshes::OnRender()
{
	Renderer renderer;

	m_Texture->Bind();


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_Shader->SetUniform4f("u_Colour", 0.9f, 0.5f, 0.2f, 1.0f);

	{
		glm::mat4 model = m_Mesh1.GetTransform();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		renderer.Draw(*m_Mesh1.GetMesh()->GetVAO(), *m_Mesh1.GetMesh()->GetIB(), *m_Shader);
		/*glLineWidth(2.5);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(m_Body1.GetPosition()->x, m_Body1.GetPosition()->y, m_Body1.GetPosition()->z);
		glVertex3f(m_Body2.GetPosition()->x, m_Body2.GetPosition()->y, m_Body2.GetPosition()->z);
		glEnd();*/
	}
	m_Shader->SetUniform4f("u_Colour", 0.3f, 0.8f, 0.9f, 1.0f);
	{
		glm::mat4 model = m_Mesh2.GetTransform();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		renderer.Draw(*m_Mesh2.GetMesh()->GetVAO(), *m_Mesh2.GetMesh()->GetIB(), *m_Shader);
	}
}

void test::TestMeshes::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	ImGui::Checkbox("WireFrame", &wireFrame);
}
