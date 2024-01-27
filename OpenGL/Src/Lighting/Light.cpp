#include "Light.h"

Light::Light()
{
	SetupDebugMesh();
}

void Light::SetRenderDebug(bool shouldRender)
{
	m_renderDebug = shouldRender;
	//if (m_debugLightMesh == NULL)
	//{
	//	SetupDebugMesh();
	//}
}

void Light::Render(glm::mat4 view, glm::mat4 projection)
{
	if (m_renderDebug)
	{
		glm::mat4 model = glm::mat4(1);
		model = glm::translate(model, m_position);
		model = glm::scale(model, glm::vec3(1, 1, 1));
		glm::mat4 mvp = projection * view * model;
		m_debugLightShader->Bind();
		m_debugLightShader->SetUniformMat4f("u_MVP", mvp);
		m_debugLightShader->SetUniform4f("u_Colour", m_diffuse.r, m_diffuse.g, m_diffuse.b, 1.0);

		m_debugLightMesh.Draw(*m_debugLightShader);
		m_debugLightShader->UnBind();
	}
}

void Light::SetShaderUniform(Shader* shader, std::string uniformName, std::string positionName, std::string ambientName, std::string diffuseName, std::string specularName)
{
	uniformName += ".";
	shader->SetUniform3f(uniformName + positionName, m_position.x, m_position.y, m_position.z);
	shader->SetUniform3f(uniformName + ambientName, m_ambient.x, m_ambient.y, m_ambient.z);
	shader->SetUniform3f(uniformName + diffuseName, m_diffuse.x, m_diffuse.y, m_diffuse.z);
	shader->SetUniform3f(uniformName + specularName, m_specular.x, m_specular.y, m_specular.z);
}

void Light::RenderImGUISettings()
{
	bool check = m_renderDebug;
	ImGui::Spacing();
	ImGui::Checkbox("Toggle Render Light", &check);
	ImGui::DragFloat3("Position", &m_position.x);
	ImGui::ColorEdit3("DiffuseColour", &m_diffuse.x);
	ImGui::ColorEdit3("AmbientColour", &m_ambient.x);
	ImGui::ColorEdit3("Specular", &m_specular.x);
	if (check != m_renderDebug)
	{
		SetRenderDebug(check);
	}
}

void Light::SetupDebugMesh()
{
	m_debugLightMesh.CreateSphere(.3f);

	m_debugLightShader = new Shader("res/shaders/Basic.shader");
	m_debugLightShader->Bind();

}
