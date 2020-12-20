#include "TestQuads.h"

test::TestQuads::TestQuads()
	: m_Shader(nullptr), m_VAO(nullptr), m_VB(nullptr), m_IB(nullptr), m_Texture(nullptr), m_Translation1(200, 200, 0), m_Translation2(400, 200, 0), 
	m_Quad1Colour(1, 1, 1, 1), m_Quad2Colour(1,1,1,1)
{
	
	float positions[] = {
		 -50.f,  -50.f, 0.0f, 0.0f,	// 0
		 50.f,  -50.f, 1.0f, 0.0f,	// 1
		 50.f,  50.f, 1.0f, 1.0f,	// 2
		 -50.f,  50.f, 0.0f, 1.0f	// 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};


	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	

	m_VAO = new VertexArray;
	m_VB = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VB, layout);
	//index buffer object (ibo)
	m_IB = new IndexBuffer(indices, 6);

	proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();

	m_Shader->SetUniform4f("u_Colour", 0.8f, 0.3f, 0.8f, 1.0f);



	m_Texture = new Texture("res/textures/Oh.png");
	m_Shader->SetUniform1i("u_Texture", 0);
}

test::TestQuads::~TestQuads()
{
	if (m_Shader)
	{
		delete m_Shader;
		m_Shader = nullptr;
	}

	if (m_VAO)
	{
		delete m_VAO;
		m_VAO = nullptr;
	}

	if (m_IB)
	{
		delete m_IB;
		m_IB = nullptr;
	}

	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}

	if (m_VB)
	{
		delete m_VB;
		m_VB = nullptr;
	}
}

void test::TestQuads::OnUpdate(float dt)
{
	
}

void test::TestQuads::OnRender()
{

	Renderer renderer;

	m_Texture->Bind();


	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	m_Shader->SetUniform4f("u_Colour", m_Quad1Colour.x, m_Quad1Colour.y, m_Quad1Colour.z, m_Quad1Colour.w);

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation1);
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		renderer.Draw(*m_VAO, *m_IB, *m_Shader);
	}

	m_Shader->SetUniform4f("u_Colour", m_Quad2Colour.x, m_Quad2Colour.y, m_Quad2Colour.z, m_Quad2Colour.w);


	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation2);
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->Bind();
		renderer.Draw(*m_VAO, *m_IB, *m_Shader);
	}

}

void test::TestQuads::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
	{
		ImGui::SliderFloat3("Translation A", &m_Translation1.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("Translation B", &m_Translation2.x, 0.0f, 960.0f);   
		
		ImGui::ColorEdit4("Colour1", &m_Quad1Colour.x);
		ImGui::ColorEdit4("Colour2", &m_Quad2Colour.x);


		// Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::DragFloat3("CameraPos", &translation.x, 0.1f, -20.f, 960.0f);
	}
}
