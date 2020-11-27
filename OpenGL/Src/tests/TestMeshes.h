#ifndef TESTMESHES_H
#define TESTMESHES_H

#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
namespace test {
	class TestMeshes : public Test
	{
	public:
		TestMeshes();
		~TestMeshes();


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

		Texture* m_Texture;
		GameObject m_Mesh1;
		GameObject m_Mesh2;

		Mesh cubeMesh;
		Mesh sphereMesh;


		Camera cam;

		bool wireFrame;
	};
}


#endif // !TESTMESHES_H

