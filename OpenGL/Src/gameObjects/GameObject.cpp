#include "GameObject.h"

GameObject::GameObject()
	: m_position(0, 0, 0)
	, m_scale(1, 1, 1)
	, m_rotation(0, 1, 0, 0)
	, m_velocity(0, 0, 0)
{
}

GameObject::GameObject(row::vector3 pos, glm::vec3 scale, float mass, row::vector3 velocity,glm::vec4 colour, std::string name)
	: m_position(pos)
	, m_scale(scale)
	, m_rotation(0, 1, 0, 0)
	, m_mass(mass)
	, m_velocity(velocity)
	, m_colour(colour)
	,m_name(name)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::BuildTransform()
{
	glm::mat4 positionMat, scaleMat, rotationMat;
	positionMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x,m_position.y,m_position.z));
	scaleMat = glm::scale(glm::mat4(1.0f), m_scale);
	rotationMat = glm::rotate(m_rotation.w, glm::vec3(m_rotation.x, m_rotation.y, m_rotation.z));

	m_localTransform = positionMat * rotationMat * scaleMat;
}

glm::mat4 GameObject::GetTransform()
{
	return m_localTransform;
}


void GameObject::Draw(Shader & shader)
{
	m_mesh->Draw(shader);
}
