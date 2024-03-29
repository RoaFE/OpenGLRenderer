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
#include "Lighting/Light.h"
#include <vector>
#include <Lighting/DirectionalLight.h>
#include "Lighting/PointLight.h"

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

		float m_FoV;

		Shader* m_Shader;
		Shader* m_StencilShader;
		Shader* m_UnlitShader;
		Texture* m_Texture;

		Model* m_Model;

		GameObject m_testCube;

		Mesh cubeMesh;
		Mesh quad;

		DirectionalLight m_dirLight;
		PointLight m_pointLight[4];

		Camera cam;
	};
}

#endif
