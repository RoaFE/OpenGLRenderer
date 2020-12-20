#include "TestFont.h"

test::TestFont::TestFont()
	: m_FoV(45)
	, m_Speed(3)
	, m_ClearColour{ 0.025f,0.0615f,0.15f,1.0f }
	, m_Step(60.f)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Colour", 0.8f, 0.3f, 0.4f, 1.0f);

	m_TextShader = new Shader("res/shaders/Text.shader");
	m_TextShader->Bind();

	cam.SetPos(0, 0, 30);

	font = new Font();
	font->LoadFont("res/fonts/arial.ttf");

	text = new Text();
	text->SetFont(*font);
	text->SetText("Hello");

}

test::TestFont::~TestFont()
{
	if (m_Shader)
	{
		delete m_Shader;
		m_Shader = nullptr;
	}


}

void test::TestFont::OnUpdate(float dt)
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

void test::TestFont::OnRender()
{
	Renderer renderer;


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void test::TestFont::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	ImGui::ColorEdit3("Text Colour", &text->m_Colour[0]);
	{
		char char_array[256];
		strcpy_s(char_array, text->m_Text.c_str());
		ImGui::InputText("Text", char_array, 256);
		text->m_Text = (char_array);
	}

}


void test::TestFont::OnRenderUI()
{
	Renderer renderer;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	m_TextShader->SetUniformMat4f("u_MVP", proj);
	text->Draw(*m_TextShader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	text->Draw(*m_TextShader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
	text->Draw(*m_TextShader);

}




