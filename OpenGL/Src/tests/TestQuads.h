#ifndef TESTQUAD_H
#define TESTQUAD_H

#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace test {

	class TestQuads : public Test
	{
	public:
		TestQuads();
		~TestQuads();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColour[4];
		glm::vec4 m_Quad1Colour;
		glm::vec4 m_Quad2Colour;
		glm::vec3 m_Translation1;
		glm::vec3 m_Translation2;

		glm::mat4 proj;
		glm::mat4 view;

		VertexArray* m_VAO;
		VertexBuffer* m_VB;
		IndexBuffer* m_IB;
		Shader* m_Shader;
		Texture* m_Texture;


	};
}


#endif
