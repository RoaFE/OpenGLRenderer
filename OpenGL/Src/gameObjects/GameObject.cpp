#include "GameObject.h"

GameObject::GameObject()
	: m_Position(0, 0, 0)
	, m_Scale(1, 1, 1)
	, m_Rotation(0, 1, 0, 0)
	, m_Velocity(0, 0, 0)
{
}

GameObject::GameObject(row::vector3 pos, glm::vec3 scale, float mass, row::vector3 velocity,glm::vec4 colour, std::string name)
	: m_Position(pos)
	, m_Scale(scale)
	, m_Rotation(0, 1, 0, 0)
	, m_Mass(mass)
	, m_Velocity(velocity)
	, m_Colour(colour)
	,m_Name(name)
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
	positionMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x,m_Position.y,m_Position.z));
	scaleMat = glm::scale(glm::mat4(1.0f), m_Scale);
	rotationMat = glm::rotate(m_Rotation.w, glm::vec3(m_Rotation.x, m_Rotation.y, m_Rotation.z));

	m_LocalTransform = positionMat * rotationMat * scaleMat;
}

glm::mat4 GameObject::GetTransform()
{
	return m_LocalTransform;
}

