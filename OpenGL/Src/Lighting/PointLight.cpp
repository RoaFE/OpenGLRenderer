#include "PointLight.h"

void PointLight::SetShaderUniform(Shader* shader, int lightNo, std::string uniformName, std::string positionName, std::string ambientName, std::string diffuseName, std::string specularName)
{
	uniformName += "[" + std::to_string(lightNo) + "].";
	shader->SetUniform3f(uniformName + positionName, m_position.x, m_position.y, m_position.z);
	shader->SetUniform3f(uniformName + ambientName, m_ambient.x, m_ambient.y, m_ambient.z);
	shader->SetUniform3f(uniformName + diffuseName, m_diffuse.x, m_diffuse.y, m_diffuse.z);
	shader->SetUniform3f(uniformName + specularName, m_specular.x, m_specular.y, m_specular.z);

	shader->SetUniform1f(uniformName + "constant", m_constant);
	shader->SetUniform1f(uniformName + "linear", m_linear);
	shader->SetUniform1f(uniformName + "quadratic", m_quadratic);

}

void PointLight::SetShaderUniform(Shader* shader, std::string uniformName, std::string positionName, std::string ambientName, std::string diffuseName, std::string specularName)
{
	uniformName += ".";
	shader->SetUniform3f(uniformName + positionName, m_position.x, m_position.y, m_position.z);
	shader->SetUniform3f(uniformName + ambientName, m_ambient.x, m_ambient.y, m_ambient.z);
	shader->SetUniform3f(uniformName + diffuseName, m_diffuse.x, m_diffuse.y, m_diffuse.z);
	shader->SetUniform3f(uniformName + specularName, m_specular.x, m_specular.y, m_specular.z);

	shader->SetUniform1f(uniformName + "constant", m_constant);
	shader->SetUniform1f(uniformName + "linear", m_linear);
	shader->SetUniform1f(uniformName + "quadratic", m_quadratic);

}

void PointLight::RenderImGUISettings()
{
	Light::RenderImGUISettings();
	ImGui::DragFloat("Constant", &m_constant, 0.05f, 0.01f, 100.f);
	ImGui::DragFloat("Linear", &m_linear, 0.05f, 0.01f, 100.f);
	ImGui::DragFloat("Quadratic", &m_quadratic, 0.05f, 0.01f, 100.f);
}
