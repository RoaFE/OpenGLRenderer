#include "TestSolarSystem.h"

test::TestSolarSystem::TestSolarSystem()
	: m_FoV(45)
	, m_Speed(2)
	, m_ClearColour{ 0.0125f,0.03075f,0.0615f,1.0f }
	, m_Step(1800.f)
	, m_TimeElapsed(0)
	, m_NumSolType(NumericalSolution::RUNGE_KUTTA_4)
{
	//m_scale = pow(10,8);
	//m_Body1.SetMass(5.9722 * pow(10,24));
	//m_Body2.SetMass(7.342 * pow(10,22));
	//scale the distance between planets
	m_Scale = 4.17e9;

	m_Bodies.push_back(new GameObject(solar_system::sun));
	m_Bodies.push_back(new GameObject(solar_system::mercury));
	m_Bodies.push_back(new GameObject(solar_system::venus));
	m_Bodies.push_back(new GameObject(solar_system::earth));
	m_Bodies.push_back(new GameObject(solar_system::mars));
	m_Bodies.push_back(new GameObject(solar_system::jupiter));
	m_Bodies.push_back(new GameObject(solar_system::saturn));
	m_Bodies.push_back(new GameObject(solar_system::uranus));
	m_Bodies.push_back(new GameObject(solar_system::neptune));
	m_Bodies.push_back(new GameObject(solar_system::pluto));
	
	for (GameObject* body : m_Bodies)
	{
		body->SetMesh(&cubeMesh);
		body->SetPosition(body->GetPosition() / m_Scale);
	}
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();

	m_Shader->SetUniform4f("u_Colour", 0.8f, 0.3f, 0.4f, 1.0f);



	m_Texture = new Texture("res/textures/Oh.png");
	m_Shader->SetUniform1i("u_Texture", 0);

	//Calculate initial acceleration for bodies
	for (GameObject* body : m_Bodies)
	{
		row::vector3 acceleration(0, 0, 0);
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalcuateAcceleration(body, otherBody, m_Scale);
		}
		body->SetAcceleration(acceleration);
		body->SetPrevAcceleration(acceleration);
		row::vector3 newVelocity = row::CalculateBodyVelocity(*body, 0);
		body->SetVelocity(newVelocity);
		row::vector3 newPosition = row::CalculateBodyPosition(*body, 0, m_Scale);
	}

	cam.SetPos(0, 0, 60);
}

test::TestSolarSystem::~TestSolarSystem()
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

	for (GameObject* body : m_Bodies)
	{
		delete body;
	}
}

void test::TestSolarSystem::OnUpdate(float dt)
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
		switch (m_NumSolType)
		{
			case NumericalSolution::EULER :
				Euler();
				m_NumSolTypeName = "Euler";
				break;
			case NumericalSolution::SEMI_EULER :
				SemiImplicitEuler();
				m_NumSolTypeName = "Semi-Implicit Euler";
				break;
			case NumericalSolution::RUNGE_KUTTA_4 :
				RungeKutta4Approach1();
				m_NumSolTypeName = "Runge Kutta fourth order";
				break;
			case NumericalSolution::RUNGE_KUTTA_4_ALT :
				RungeKutta4Approach2();
				m_NumSolTypeName = "Runge Kutta fourth order second approach";
				break;
		default:
			break;
		}
	}


	proj = cam.GetProj();
	view = cam.GetView();
	m_TimeElapsed += m_Step * m_Speed;
}

void test::TestSolarSystem::OnRender()
{
	Renderer renderer;

	m_Texture->Bind();


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GameObject* body : m_Bodies)
	{
		glm::vec4 colour = body->GetColour();
		m_Shader->SetUniform4f("u_Colour", colour.r,colour.g,colour.b,colour.a);

		{
			glm::mat4 model = body->GetTransform();
			glm::mat4 mvp = proj * view * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Shader->Bind();
			renderer.Draw(*body->GetMesh()->GetVAO(), *body->GetMesh()->GetIB(), *m_Shader);
		}
	}
}


void test::TestSolarSystem::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear Colour", m_ClearColour);
	float scaledTime = m_TimeElapsed;
	if (scaledTime > 60)
	{
		scaledTime /= 60;
		if (scaledTime > 60)
		{
			scaledTime /= 60;
			if (scaledTime > 24)
			{
				scaledTime /= 24;
				if (scaledTime > 365)
				{
					scaledTime /= 365;
					ImGui::TextColored(ImVec4(8, 8, 0, 1), "Time Elapsed: %.3f years", scaledTime);
				}
				else
				{
					ImGui::TextColored(ImVec4(8, 8, 0, 1), "Time Elapsed: %.3f days", scaledTime);
				}
			}
			else
			{
				ImGui::TextColored(ImVec4(8, 8, 0, 1), "Time Elapsed: %.3f hr", scaledTime);
			}
		}
		else
		{
			ImGui::TextColored(ImVec4(8, 8, 0, 1), "Time Elapsed: %.3f min", scaledTime);
		}
		
	}
	else
	{
		ImGui::TextColored(ImVec4(8, 8, 0, 1), "Time Elapsed: %.3f sec", scaledTime);
	}
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(8, 8, 0, 1),"\tTime step %.2fs", m_Step);
	int numSolType = m_NumSolType;
	ImGui::DragInt("Numerical Solution Type", &numSolType, 0.05f, 0, 3);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::Text(m_NumSolTypeName.c_str());
		ImGui::EndTooltip();
	}
	m_NumSolType = (NumericalSolution)numSolType;
	{
		for (GameObject* body : m_Bodies)
		{
			if(ImGui::CollapsingHeader(body->GetName().c_str()))
			{
				ImGui::Text("Position| X:%f Y:%f Z:%f", body->GetPosition().x, body->GetPosition().y, body->GetPosition().z);
				ImGui::Text("Vel: %fm/s", body->GetVelocity().Magnitude());
				ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
				ImGui::Text("Acc: %fm/s^2", body->GetAcceleration().Magnitude());
				ImGui::Text("Force: %fN", body->GetMass() * body->GetAcceleration().Magnitude());
				std::string name = body->GetName();
				if(ImGui::Button(("Center on " + name).c_str()))
				{
					cam.SetPos(row::RowToGlm(body->GetPosition()) + (glm::vec3(body->GetScale()->x, body->GetScale()->y, body->GetScale()->z) * -20.f * cam.GetDirection()));
				}
			}
			else if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text("Position| X:%f Y:%f Z:%f", body->GetPosition().x, body->GetPosition().y, body->GetPosition().z);
				ImGui::Text("Vel: %fm/s", body->GetVelocity().Magnitude());
				ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
				ImGui::Text("Acc: %fm/s^2", body->GetAcceleration().Magnitude());
				ImGui::Text("Force: %fN", body->GetMass() * body->GetAcceleration().Magnitude());
				ImGui::EndTooltip();
			}
		}
		//ImGui::TextColored(ImVec4(1.0, 8.0, 3.0, 1.0), "Distance: %fm", (m_Body1.GetPosition() - m_Body2.GetPosition()).Magnitude());
		//ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
		//ImGui::TextColored(ImVec4(1.0, 8.0, 3.0, 1.0), "Scaled Distance: %fm", (m_Body1.GetPosition() - m_Body2.GetPosition()).Magnitude() * m_Scale);
		//ImGui::Separator();
		//ImGui::Text("Position| X:%f Y:%f Z:%f", m_Body1.GetPosition().x, m_Body1.GetPosition().y, m_Body1.GetPosition().z);
		//ImGui::Text("Vel: %fm/s", m_Body1.GetVelocity().Magnitude());            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
		//ImGui::Text("Acc: %fm/s^2", m_Body1.GetAcceleration().Magnitude());
		//ImGui::Text("Force: %fN", m_Body1.GetMass() * m_Body1.GetAcceleration().Magnitude());
		//ImGui::Separator();
		//ImGui::Text("Position| X:%f Y:%f Z:%f", m_Body2.GetPosition().x, m_Body2.GetPosition().y, m_Body2.GetPosition().z);
		//ImGui::Text("Vel: %fm/s", m_Body2.GetVelocity().Magnitude());
		//ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetWindowWidth() / 2);
		//ImGui::Text("Acc: %fm/s^2", m_Body2.GetAcceleration().Magnitude());
		//ImGui::Text("Force: %fN", m_Body2.GetMass() * m_Body2.GetAcceleration().Magnitude());
		//ImGui::Separator();
		ImGui::DragFloat("FoV", &m_FoV, 0.5, 30, 180);
		ImGui::DragFloat("Speed", &m_Speed, 0.5, 1, 1000);
		
		
		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);
	}
}

void test::TestSolarSystem::Euler()
{
	//Loop through every body
	for (GameObject* body : m_Bodies)
	{
		//calculate the total acceleration being applied by every other body within the system
		row::vector3 acceleration(0, 0, 0);
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalcuateAcceleration(body, otherBody, m_Scale);
		}
		body->SetAcceleration(acceleration);
		row::vector3 newVelocity = row::CalculateBodyVelocity(*body, m_Step);
		row::vector3 newPosition = row::CalculateBodyPosition(*body, m_Step, m_Scale);
		body->SetVelocity(newVelocity);
		body->SetPosition(newPosition);

		body->BuildTransform();
	}
}

void test::TestSolarSystem::SemiImplicitEuler()
{
	//Loop through every body
	for (GameObject* body : m_Bodies)
	{
		//calculate the total acceleration being applied by every other body within the system
		row::vector3 acceleration(0, 0, 0);
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalcuateAcceleration(body, otherBody, m_Scale);
		}
		body->SetAcceleration(acceleration);
		row::vector3 newVelocity = row::CalculateBodyVelocity(*body, m_Step);
		//Semi-implicit use the Vn+1 velocity in the position calculation
		body->SetVelocity(newVelocity);
		row::vector3 newPosition = row::CalculateBodyPosition(*body, m_Step, m_Scale);
		body->SetPosition(newPosition);

		body->BuildTransform();
	}
}

//Original approach with updated distance
void test::TestSolarSystem::RungeKutta4Approach1()
{
	//Loop through every body
	for (GameObject* body : m_Bodies)
	{
		//calculate the total acceleration being applied by every other body within the system
		row::vector3 acceleration(0, 0, 0);
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalculateBodyAccelerationRK4(body, otherBody, m_Step, m_Scale);
		}
		//Calculate the average Acceleration based on the improved Euler implementation in 
		//Graitational N-Body SImulations Tools and Algorithims
		//row::vector3 avgAcceleration = (acceleration + body->GetPrevAcceleration()) * 0.5f;
		body->SetAcceleration(acceleration);
		body->SetPrevAcceleration(acceleration);
		row::vector3 newVelocity = row::CalculateBodyVelocity(*body, m_Step);
		//Semi-implicit use the Vn+1 velocity in the position calculation
		body->SetVelocity(newVelocity);
		row::vector3 newPosition = row::CalculateBodyPosition(*body, m_Step, m_Scale);
		body->SetPosition(newPosition);

		body->BuildTransform();
	}
}

//implementation based off of notes provided by Craig
void test::TestSolarSystem::RungeKutta4Approach2()
{
	//Loop through every body
	for (GameObject* body : m_Bodies)
	{
		row::vector3 acceleration(0, 0, 0);
		row::vector3 k1, k2, k3, k4, ka, kb, kc, kd;
		GameObject temp = *body;
		//ka
		temp.SetVelocity (body->GetVelocity() * m_Step);
		ka = temp.GetVelocity();
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalcuateAcceleration(body, otherBody, m_Scale);
		}
		//k1
		temp.SetAcceleration(acceleration);
		k1 = temp.GetAcceleration();
		//ka / 2 - Rj
		temp.SetPosition(body->GetPosition() + ((temp.GetVelocity() / 2)/m_Scale));

		//kb	h(vi + k1/2)
		temp.SetVelocity((body->GetVelocity() + (temp.GetAcceleration() / 2)) * m_Step);
		kb = temp.GetVelocity();
		acceleration = { 0,0,0 };
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalcuateAcceleration(&temp, otherBody, m_Scale);
		}
		//k2
		temp.SetAcceleration(acceleration);
		k2 = temp.GetAcceleration();
		//kb / 2 - Rj
		temp.SetPosition(body->GetPosition() + ((temp.GetVelocity() / 2) / m_Scale));

		//kc	h(vi + k2/2)
		temp.SetVelocity((body->GetVelocity() + (temp.GetAcceleration() / 2)) * m_Step);
		kc = temp.GetVelocity();
		acceleration = { 0,0,0 };
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalcuateAcceleration(&temp, otherBody, m_Scale);
		}
		//k3
		temp.SetAcceleration(acceleration);
		k3 = temp.GetAcceleration();
		//kc / 2 - Rj
		temp.SetPosition(body->GetPosition() + ((temp.GetVelocity() / 2) / m_Scale));

		//kd	h(vi + k3)
		temp.SetVelocity((body->GetVelocity() + temp.GetAcceleration()) * m_Step);

		kd = temp.GetVelocity();

		acceleration = { 0,0,0 };
		for (GameObject* otherBody : m_Bodies)
		{
			if (otherBody == body)
				continue;
			acceleration += row::CalcuateAcceleration(&temp, otherBody, m_Scale);
		}
		//k4
		temp.SetAcceleration(acceleration);
		k4 = temp.GetAcceleration();

		row::vector3 newVelocity = body->GetVelocity() + ((k1 + (k2 * 2) + (k3 * 2) + k4) / 6);
		body->SetVelocity(newVelocity);
		row::vector3 newPosition = body->GetPosition() + (((ka + (kb * 2) + (kc * 2) + kd) / 6) / m_Scale);
		body->SetPosition(newPosition);

		body->BuildTransform();
	}
}




