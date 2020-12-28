#include "TestCube.h"

test::TestCube::TestCube()
	: m_Shader(nullptr), m_Texture(nullptr), m_Translation(0, 0, 0), m_Scale(1, 1, 1),
	m_Rotation(0, 0, 0, 0), m_FoV(45),m_CameraControl(true)
{
	cubeMesh.CreateCube();
	cube.SetMesh(&cubeMesh);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();

	m_Shader->SetUniform4f("u_Colour", 0.8f, 0.3f, 0.4f, 1.0f);



	m_Texture = new Texture("res/textures","Oh.png");
	m_Shader->SetUniform1i("u_Texture", 0);
}

test::TestCube::~TestCube()
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

void test::TestCube::OnUpdate(float dt)
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

	cube.SetPosition(row::vector3(m_Translation.x, m_Translation.y, m_Translation.z));
	cube.SetRotation(m_Rotation);
	cube.SetScale(m_Scale);
	cube.BuildTransform();
	proj = cam.GetProj();
	view = cam.GetView();
}

void test::TestCube::OnRender()
{

	Renderer renderer;

	m_Texture->Bind();


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	m_Shader->SetUniform4f("u_Colour", 0.5, 0.2, 0.8, 1.0);

	{
		glm::mat4 model = cube.GetTransform();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		renderer.Draw(*cube.GetMesh()->GetVAO(), *cube.GetMesh()->GetIB(), *m_Shader);
	}
}

void test::TestCube::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	{
		ImGui::DragFloat3("Translation", &m_Translation.x,0.05f, -400.f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::DragFloat3("Scale", &m_Scale.x,0.5f, 0.0f, 100.0f);   
		ImGui::DragFloat3("Rotation Axis", &m_Rotation.x, 0.05f, -1, 1.0);
		ImGui::SliderFloat("Angle", &m_Rotation.w, -180, 180);
		ImGui::DragFloat("FoV", &m_FoV,0.5, 30, 180);
		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);
	}
}
