#ifndef TestDrawing_H
#define TestDrawing_H

#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "gameObjects/GameObject.h"
#include "gameObjects/Mesh.h"
#include "Camera.h"
namespace test {

	class TestDrawing : public Test
	{
	public:
		TestDrawing();
		~TestDrawing();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColour[4];
		glm::vec3 m_Scale;
		glm::vec4 m_Rotation;
		glm::vec3 m_Translation;

		glm::mat4 proj;
		glm::mat4 view;

		glm::vec3 mouseRay;
		glm::vec3 camPos;

		float m_FoV;

		Shader* m_Shader;
		Texture* m_Texture;
		GameObject cube;
		Mesh cubeMesh;

		Camera cam;

		bool m_CameraControl;
		bool m_SpaceHold;

	};
}

#endif
