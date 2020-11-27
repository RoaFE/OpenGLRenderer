#ifndef TEST2BODY_H
#define TEST2BODY_H


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
	class Test2Body : public Test
	{
	public:
		Test2Body();
		~Test2Body();


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


		GameObject m_Body1;
		GameObject m_Body2;
		Texture* m_Texture;

		float m_Scale;
		float m_Step;
		Mesh cubeMesh;


		Camera cam;


	};


}

#endif
