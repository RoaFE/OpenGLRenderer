#include "Test2Body.h"

test::Test2Body::Test2Body()
	: m_FoV(45)
	, m_Speed(3)
	, m_ClearColour{ 0.025f,0.0615f,0.15f,1.0f }
	, m_Step(60.f)
{
	//m_scale = pow(10,8);
	//m_Body1.SetMass(5.9722 * pow(10,24));
	//m_Body2.SetMass(7.342 * pow(10,22));
	m_Scale = 9.375e9;
	
	cubeMesh.CreateCube();

	m_Body1 = solar_system::sun;
	//m_Body1.SetMass(5 * pow(10, 18));
	m_Body2 = solar_system::earth;
	m_Body2.SetPosition(m_Body2.GetPosition() / m_Scale);
	//m_Body2.SetMass(5 * pow(10, 18));
	
	m_Body1.SetMesh(&cubeMesh);
	m_Body2.SetMesh(&cubeMesh);
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();

	m_Shader->SetUniform4f("u_Colour", 0.8f, 0.3f, 0.4f, 1.0f);



	m_Texture = new Texture("res/textures/Oh.png");
	m_Shader->SetUniform1i("u_Texture", 0);

	row::UpdateBodyEuler(&m_Body2, &m_Body1, 0,m_Scale);
	row::UpdateBodyEuler(&m_Body1, &m_Body2, 0,m_Scale);
	m_Body1.SetPrevAcceleration(m_Body1.GetAcceleration());
	m_Body2.SetPrevAcceleration(m_Body2.GetAcceleration());
	cam.SetPos(0, 0, 30);
}

test::Test2Body::~Test2Body()
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

void test::Test2Body::OnUpdate(float dt)
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

	for (int i = 0; i < m_Speed; i++)
	{
		row::UpdateBodyImprovedEuler(&m_Body1, &m_Body2, m_Step,m_Scale);
		row::UpdateBodyImprovedEuler(&m_Body2, &m_Body1, m_Step, m_Scale);
	}

	

	m_Body1.BuildTransform();
	m_Body2.BuildTransform();
	proj = cam.GetProj();
	view = cam.GetView();
}

void test::Test2Body::OnRender()
{
	Renderer renderer;

	m_Texture->Bind();


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_Shader->SetUniform4f("u_Colour", 0.9, 0.5, 0.2, 1.0);

	{
		glm::mat4 model = m_Body1.GetTransform();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		renderer.Draw(*m_Body1.GetMesh()->GetVAO(), *m_Body1.GetMesh()->GetIB(), *m_Shader);
		/*glLineWidth(2.5);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(m_Body1.GetPosition()->x, m_Body1.GetPosition()->y, m_Body1.GetPosition()->z);
		glVertex3f(m_Body2.GetPosition()->x, m_Body2.GetPosition()->y, m_Body2.GetPosition()->z);
		glEnd();*/
	}
	m_Shader->SetUniform4f("u_Colour", 0.3, 0.8, 0.9, 1.0);
	{
		glm::mat4 model = m_Body2.GetTransform();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		renderer.Draw(*m_Body2.GetMesh()->GetVAO(), *m_Body2.GetMesh()->GetIB(), *m_Shader);
	}
}


void test::Test2Body::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	{
		ImGui::TextColored(ImVec4(1.0, 8.0, 3.0, 1.0), "Distance: %fm", (m_Body1.GetPosition() - m_Body2.GetPosition()).Magnitude());
		ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
		ImGui::TextColored(ImVec4(1.0, 8.0, 3.0, 1.0), "Scaled Distance: %fm", (m_Body1.GetPosition() - m_Body2.GetPosition()).Magnitude() * m_Scale);
		ImGui::Separator();
		ImGui::Text("Position| X:%f Y:%f Z:%f", m_Body1.GetPosition().x, m_Body1.GetPosition().y, m_Body1.GetPosition().z);
		ImGui::Text("Vel: %fm/s", m_Body1.GetVelocity().Magnitude());            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
		ImGui::Text("Acc: %fm/s^2", m_Body1.GetAcceleration().Magnitude());
		ImGui::Text("Force: %fN", m_Body1.GetMass() * m_Body1.GetAcceleration().Magnitude());
		ImGui::Separator();
		ImGui::Text("Position| X:%f Y:%f Z:%f", m_Body2.GetPosition().x, m_Body2.GetPosition().y, m_Body2.GetPosition().z);
		ImGui::Text("Vel: %fm/s", m_Body2.GetVelocity().Magnitude());
		ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
		ImGui::Text("Acc: %fm/s^2", m_Body2.GetAcceleration().Magnitude());
		ImGui::Text("Force: %fN", m_Body2.GetMass() * m_Body2.GetAcceleration().Magnitude());
		ImGui::Separator();
		ImGui::DragFloat("FoV", &m_FoV, 0.5, 30, 180);
		ImGui::DragFloat("Speed", &m_Speed, 0.5, 1, 1000);
		
		
		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);
	}
}




