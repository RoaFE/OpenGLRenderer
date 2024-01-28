#include "DirectionalLight.h"

void DirectionalLight::SetShaderUniform(Shader* shader, std::string uniformName, std::string positionName, std::string ambientName, std::string diffuseName, std::string specularName)
{
	Light::SetShaderUniform(shader, uniformName, positionName, ambientName, diffuseName, specularName);
}

void DirectionalLight::RenderImGUISettings()
{
	bool check = m_renderDebug;
	ImGui::Spacing();
	ImGui::Checkbox("Toggle Render Light", &check);
	ImGui::DragFloat3("Direction", &m_position.x);
	ImGui::ColorEdit3("DiffuseColour", &m_diffuse.x);
	ImGui::ColorEdit3("AmbientColour", &m_ambient.x);
	ImGui::ColorEdit3("Specular", &m_specular.x);
	if (check != m_renderDebug)
	{
		SetRenderDebug(check);
	}
}
