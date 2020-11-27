#include "TestClearColour.h"



test::TestClearColour::TestClearColour() : m_ClearColour { 0.2f,0.3f,0.8f,1.0f}
{
}

test::TestClearColour::~TestClearColour()
{
}

void test::TestClearColour::OnUpdate(float dt)
{
}

void test::TestClearColour::OnRender()
{
	GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColour::OnImGuiRender()
{
	ImGui::ColorEdit4("clear Colour", m_ClearColour);
}
