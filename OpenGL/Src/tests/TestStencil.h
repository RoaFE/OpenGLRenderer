#ifndef TestStencil_H
#define TestStencil_H

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
#include "RowUtil.h"
#include <vector>


namespace test {

	class TestStencil : public Test
	{
	public:
		TestStencil();
		~TestStencil();


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

		float m_FoV;

		Shader* m_Shader;
		Shader* m_StencilShader;
		Texture* m_Texture;
		std::vector<GameObject*> cubes;
		Mesh cubeMesh;
		Mesh quad;

		Camera cam;

		bool m_CameraControl;
		bool m_SpaceHold;

	};
}

#endif
