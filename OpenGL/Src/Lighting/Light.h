#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string.h>
#include "Shader.h"
#include "imgui/imgui.h"
#include "gameObjects/Mesh.h";
#include "gameObjects/GameObject.h"


class Light
{
public:

	Light();

	void SetPosition(glm::vec3 pos) { m_position = pos; }
	glm::vec3 GetPosition() { return m_position; }
	void SetAmbient(glm::vec3 ambient) { m_ambient = ambient; }
	glm::vec3 GetAmbient() { return m_ambient; }
	void SetDiffuse(glm::vec3 diffuse) { m_diffuse = diffuse; }
	glm::vec3 GetDiffuse() { return m_diffuse; }	
	void SetSpecular(glm::vec3 specular) { m_specular = specular; }
	glm::vec3 GetSpecular() { return m_specular; }	
	
	void SetRenderDebug(bool shouldRender);

	void Render(glm::mat4 view, glm::mat4 projection);

	virtual void SetShaderUniform(Shader* shader, std::string uniformName = "light", std::string positionName = "position", std::string AmbientName = "ambient", std::string DiffuseName = "diffuse", std::string SpecularName = "specular");
	virtual void RenderImGUISettings();


protected:
	glm::vec3 m_position = glm::vec3(0,10,0);
	glm::vec3 m_ambient = glm::vec3(0.1f,0.1f,0.1f);
	glm::vec3 m_diffuse = glm::vec3(0.84f,0.54f,0.11f);
	glm::vec3 m_specular = glm::vec3(1.0f,1.0f,1.0f);
	bool m_renderDebug = true;


	Mesh m_debugLightMesh;
	Shader* m_debugLightShader;

	void SetupDebugMesh();
};

