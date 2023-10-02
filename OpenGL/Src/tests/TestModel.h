#ifndef TestModel_H
#define TestModel_H

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
#include "gameObjects/Model.h"
#include <vector>


namespace test {

	class TestModel : public Test
	{
	public:
		TestModel();
		~TestModel();


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

		glm::vec3 m_lightColour = glm::vec3(0, 1, 0.6);
		glm::vec3 m_ambientColour = glm::vec3(0,0.1,0.1);
		float m_ambientStrength = 0.6;
		glm::vec3 m_lightPos = glm::vec3(3, 3, 2);

		float m_FoV;

		Shader* m_Shader;
		Shader* m_StencilShader;
		Texture* m_Texture;

		Model* m_Model;

		GameObject m_plane;

		Mesh cubeMesh;
		Mesh quad;

		Camera cam;
	};
}

#endif
