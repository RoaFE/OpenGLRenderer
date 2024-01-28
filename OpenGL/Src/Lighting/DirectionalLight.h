#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:


	void SetShaderUniform(Shader* shader, std::string uniformName = "dirLight", std::string positionName = "direction", std::string ambientName = "ambient", std::string diffuseName = "diffuse", std::string specularName = "specular") override;

	void RenderImGUISettings() override;
};

