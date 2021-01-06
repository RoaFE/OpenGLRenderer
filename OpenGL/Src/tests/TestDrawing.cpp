#include "TestDrawing.h"

test::TestDrawing::TestDrawing()
	: m_Shader(nullptr), m_Texture(nullptr), m_Translation(0, 0, 0), m_Scale(1, 1, 1),
	m_Rotation(0, 1, 0, 0), m_FoV(45),m_CameraControl(true)
{
	cubeMesh.CreatePlane(2,4);
	cube.SetMesh(&cubeMesh);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();

	m_Shader->SetUniform4f("u_Colour", 0.8f, 0.3f, 0.4f, 1.0f);



	//m_Texture = new Texture("res/textures","Oh.png");
	//m_Shader->SetUniform1i("u_Texture", 0);
}

test::TestDrawing::~TestDrawing()
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

void test::TestDrawing::OnUpdate(float dt)
{


	if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{

		double xPos, yPos;
		glfwGetCursorPos(m_Window, &xPos, &yPos);

		mouseRay = cam.ScreenToWorldSpace(glm::vec2(xPos, yPos), m_Window);
    	camPos = cam.GetPos();

		m_Translation = cam.GetPos();
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

	cube.SetPosition(row::vector3(m_Translation.x, m_Translation.y, m_Translation.z));
	cube.SetRotation(m_Rotation);
	cube.SetScale(m_Scale);
	cube.BuildTransform();
	proj = cam.GetProj();
	view = cam.GetView();
}

void test::TestDrawing::OnRender()
{

	Renderer renderer;

	//m_Texture->Bind();


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_Shader->SetUniform4f("u_Colour", 0.5, 0.2, 0.8, 1.0);

	{
		glm::mat4 model = cube.GetTransform();
		//glm::mat4 model = glm::mat4(1.0);
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		cube.Draw(*m_Shader);
	}



	glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	glm::mat4 mvp = proj * view * model;
	m_Shader->SetUniform4f("u_Colour", 0.8, 0.2, 0.3, 1.0);
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	m_Shader->Bind();
	renderer.DrawLine(*m_Shader,camPos, mouseRay);
	renderer.DrawLine(*m_Shader, glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec4(1.0, 1.0, 0.0, 1.0), 5);
	
}

void test::TestDrawing::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	{
		ImGui::TextColored(ImVec4(0.86, 0.32, 0.32, 1.0), "X%.3f , Y%.3f, Z%.3f", camPos.x, camPos.y, camPos.z);
		//ImGui::DragFloat3("Translation", &m_Translation.x,0.05f, -400.f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("Scale", &m_Scale.x,0.5f, 0.0f, 100.0f);   
		//ImGui::DragFloat3("Rotation Axis", &m_Rotation.x, 0.05f, -1, 1.0);
		//ImGui::SliderFloat("Angle", &m_Rotation.w, -180, 180);
		ImGui::DragFloat("FoV", &m_FoV,0.5, 30, 180);

		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);
	}
}
