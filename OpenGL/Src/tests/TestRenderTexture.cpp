#include "TestRenderTexture.h"



test::TestRenderTexture::TestRenderTexture()
{
}

test::TestRenderTexture::~TestRenderTexture()
{
}

void test::TestRenderTexture::OnUpdate(float dt)
{
}

void test::TestRenderTexture::OnRender()
{
	GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestRenderTexture::OnImGuiRender()
{
	//ImGui::ColorEdit4("clear Colour", m_ClearColour);
}
