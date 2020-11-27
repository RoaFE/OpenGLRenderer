#ifndef TESTSOLARSYSTEM_H
#define TESTSOLARSYSTEM_H


#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "gameObjects/Mesh.h"
#include "gameObjects/GameObject.h"
#include "Camera.h"
#include "rowMath/NumericalSolution.h"

enum NumericalSolution
{
	EULER,SEMI_EULER, RUNGE_KUTTA_4, RUNGE_KUTTA_4_ALT
};

namespace test {
	class TestSolarSystem : public Test
	{
	public:
		TestSolarSystem();
		~TestSolarSystem();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColour[4];

		glm::mat4 proj;
		glm::mat4 view;

		float m_FoV;
		float m_Speed;
		Shader* m_Shader;


		std::vector<GameObject*> m_Bodies;
		Texture* m_Texture;

		float m_Scale;
		float m_Step;

		Mesh cubeMesh;
		Camera cam;

		float m_TimeElapsed;

		void Euler();
		void SemiImplicitEuler();
		void RungeKutta4Approach1();
		void RungeKutta4Approach2();

		NumericalSolution m_NumSolType;
		std::string m_NumSolTypeName;

	};


}

#endif
