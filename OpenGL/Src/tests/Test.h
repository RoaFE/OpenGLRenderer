#ifndef TEST_H
#define TEST_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "imgui/imgui.h"

#include <functional>
#include <vector>
namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}


		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnImGuiRenderMenuBar() {};
		virtual void ScrollCallBack(double offset) {};
		void SetWindow(GLFWwindow* window) { m_Window = window; }
	protected:
		GLFWwindow* m_Window;
	};


	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{

			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Test*& m_CurTest;
		std::vector < std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}

#endif