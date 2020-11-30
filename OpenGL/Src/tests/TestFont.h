#ifndef TESTFONT_H
#define TESTFONT_H
#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "gameObjects/Mesh.h"
#include "gameObjects/GameObject.h"
#include "Camera.h"
#include "rowMath/NumericalSolution.h"
#include "Font.h"

namespace test {
	class TestFont : public Test
	{
	public:
		TestFont();
		~TestFont();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnRenderUI() override;

	private:
		float m_ClearColour[4];

		glm::mat4 proj;
		glm::mat4 view;

		float m_FoV;
		float m_Speed;
		Shader* m_Shader;
		Shader* m_TextShader;


		float m_Scale;
		float m_Step;

		Camera cam;

		Font* font;

	};


}

#endif
