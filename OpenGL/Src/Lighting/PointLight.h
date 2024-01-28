#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	void SetShaderUniform(Shader* shader, int lightNo = 0, std::string uniformName = "pointLights", std::string positionName = "position", std::string ambientName = "ambient", std::string diffuseName = "diffuse", std::string specularName = "specular");
	void SetShaderUniform(Shader* shader, std::string uniformName = "pointLight", std::string positionName = "position", std::string ambientName = "ambient", std::string diffuseName = "diffuse", std::string specularName = "specular") override;
	void RenderImGUISettings() override;

private:
	float m_constant = 1.0f;
	float m_linear = 2.0f;
	float m_quadratic = 16.f;
};

