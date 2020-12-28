#include <freetype/freetype.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


#include "tests/TestClearColour.h"
#include "tests/TestQuads.h"
#include "tests/TestCube.h"
#include "tests/Test2Body.h"
#include "tests/TestSolarSystem.h"
#include "tests/TestMeshes.h"
#include "tests/TestFont.h"
#include "tests/TestRenderTexture.h"
#include "tests/TestDepthTest.h"
#include "tests/TestStencil.h"
#include "tests/TestModel.h"

double yScroll;

//Scroll Call back
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	yScroll += yoffset;
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	GLFWwindow* window;
	bool fullscreen = false;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	bool renderUI = true;
	bool pressed = false;

	GLFWmonitor* primary = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(primary);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Renderer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//glfwSetWindowAspectRatio(window, 16, 9);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1);


	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}
	FT_Face face;
	if (FT_New_Face(ft, "res/fonts/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}


	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}


	std::cout << glGetString(GL_VERSION) << std::endl;
	{


		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		Renderer renderer;

		Mesh mesh;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();


		glfwSetScrollCallback(window, scroll_callback);
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		testMenu->SetWindow(window);
		currentTest = testMenu;

		//testMenu->RegisterTest<test::TestClearColour> ("Clear Colour");
		//testMenu->RegisterTest<test::TestDepthTest>("Test Cube");
		testMenu->RegisterTest<test::TestCube>("Test Cube");
		testMenu->RegisterTest<test::Test2Body>("Test 2 Body");
		testMenu->RegisterTest<test::TestFont>("Test Font");
		testMenu->RegisterTest<test::TestQuads>("Test Texture");
		testMenu->RegisterTest<test::TestDepthTest>("Test Depth Test");
		//testMenu->RegisterTest<test::TestStencil>("Test Outline/Stencil");
		testMenu->RegisterTest<test::TestModel>("Test Model");
		//testMenu->RegisterTest<test::TestSolarSystem>("Test Solar System");
		//testMenu->RegisterTest<test::TestMeshes>("Test Mesh");
		/* Loop until the user closes the window */
		float lastTime, currentTime, frameTime;
		lastTime = (float)glfwGetTime();

		while (!glfwWindowShouldClose(window))
		{
			currentTime = (float)glfwGetTime();
			frameTime = currentTime - lastTime;
			/* Render here */
			GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
			renderer.Clear();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			ImGui_ImplGlfwGL3_NewFrame();

			if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && !pressed)
			{
				renderUI = !renderUI;
				pressed = true;
			}
			else if (pressed && glfwGetKey(window, GLFW_KEY_F2) != GLFW_PRESS)
			{
				pressed = false;
			}
			
			if (currentTest)
			{
				currentTest->ScrollCallBack(yScroll);
				currentTest->OnUpdate(frameTime);

				currentTest->OnRender();				
				if (renderUI)
				{
					currentTest->OnRenderUI();
					if (ImGui::BeginMainMenuBar())
					{
						if (currentTest != testMenu && ImGui::Button("<-"))
						{
							delete currentTest;
							currentTest = testMenu;
						}
						ImGui::Text("OpenGl-Renderer");
						ImGui::Separator();
						if (currentTest)
						{
							currentTest->OnImGuiRenderMenuBar();
						}
						ImGui::SameLine(ImGui::GetWindowWidth() - 390.f);
						ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
						//if (ImGui::Button("F"))
						//{
						//	fullscreen = !fullscreen;
						//	if (fullscreen)
						//	{
						//		glfwMaximizeWindow(window);
						//		glfwSetWindowSize(window, mode->width, mode->height);
						//		glViewport(0, 0, mode->width, mode->height);
						//	}
						//	else
						//	{
						//		glfwRestoreWindow(window);
						//		glfwSetWindowSize(window, 960, 540);
						//		glViewport(0, 0, 960, 540);
						//	}
						//}
						if (ImGui::Button("X"))
						{
							glfwSetWindowShouldClose(window, GLFW_TRUE);
						}
						//ImGui::SameLine();
						//ImGui::Text("DeltaTime: %.5f s", frameTime);

						ImGui::EndMainMenuBar();
					}
					currentTest->OnImGuiRender();
				}
				yScroll = 0;
			}
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
			lastTime = currentTime;
		}
		delete currentTest;
		if (currentTest != testMenu)
		{
			delete testMenu;
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
