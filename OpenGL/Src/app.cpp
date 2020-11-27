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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "N-Body", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	{


		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_CULL_FACE));


		Renderer renderer;

		Mesh mesh;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		testMenu->SetWindow(window);
		currentTest = testMenu;

		//testMenu->RegisterTest<test::TestClearColour> ("Clear Colour");
		//testMenu->RegisterTest<test::TestQuads>("Test Quad");
		//testMenu->RegisterTest<test::TestCube>("Test Cube");
		testMenu->RegisterTest<test::TestCube>("Test Cube");
		//testMenu->RegisterTest<test::Test2Body>("Test 2 Body");
		//testMenu->RegisterTest<test::TestSolarSystem>("Test Solar System");
		//testMenu->RegisterTest<test::TestMeshes>("Test Mesh");
		/* Loop until the user closes the window */
		float lastTime, currentTime, frameTime;
		lastTime = glfwGetTime();
		while (!glfwWindowShouldClose(window))
		{
			currentTime = glfwGetTime();
			frameTime = currentTime - lastTime;
			/* Render here */
			GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
			renderer.Clear();


			ImGui_ImplGlfwGL3_NewFrame();


			if (ImGui::BeginMainMenuBar())
			{
				ImGui::Text("N-Body Simulation");
				ImGui::SameLine(ImGui::GetWindowWidth() - 335.f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				//ImGui::SameLine();
				//ImGui::Text("DeltaTime: %.5f s", frameTime);

				ImGui::EndMainMenuBar();
			}

			if (currentTest)
			{
				currentTest->OnUpdate(frameTime);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
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
