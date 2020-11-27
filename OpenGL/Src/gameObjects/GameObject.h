#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "Mesh.h"
#include "rowMath/rowMath.h"
#include <string>

class GameObject
{
public:
	GameObject();
	GameObject(row::vector3 pos, glm::vec3 scale, float mass, row::vector3 velocity,glm::vec4 colour, std::string name);
	~GameObject();

	void Update(float dt);

	void BuildTransform();
	glm::mat4 GetTransform();
	void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
	Mesh* GetMesh() { return m_Mesh; };
	void SetPosition(row::vector3 pos) { m_Position = pos; }
	void AddPosition(row::vector3 pos) { m_Position += pos; }
	void SetVelocity(row::vector3 vel) { m_Velocity = vel; }
	void SetAcceleration(row::vector3 acc) { m_Acceleration = acc; }
	void SetPrevAcceleration(row::vector3 acc) { m_PrevAcceleration = acc; }
	void SetScale(glm::vec3 scale) { m_Scale = scale; }
	void SetRotation(glm::vec4 rot) { m_Rotation = rot; }
	row::vector3 GetPosition() { return m_Position; }
	row::vector3 GetVelocity() { return m_Velocity; }
	row::vector3 GetAcceleration() { return m_Acceleration; }
	row::vector3 GetPrevAcceleration() { return m_PrevAcceleration; }
	glm::vec3* GetScale() { return &m_Scale; }
	glm::vec4* GetRotation() { return &m_Rotation; }
	glm::vec4 GetColour() { return m_Colour; }
	float GetMass() { return m_Mass; }
	void SetMass(float mass) { m_Mass = mass; }
	std::string GetName() { return m_Name; }

private:
	row::vector3 m_Position;
	glm::vec4 m_Rotation;
	glm::vec3 m_Scale;
	glm::mat4 m_LocalTransform;

	row::vector3 m_Acceleration;
	row::vector3 m_Velocity;
	row::vector3 m_PrevAcceleration;
	float m_Mass;

	Mesh* m_Mesh;
	glm::vec4 m_Colour;

	std::string m_Name;

};

namespace solar_system
{
	static GameObject sun(row::vector3(0, 0, 0), glm::vec3(7, 7, 7), 1.9885e30, row::vector3(0, 0, 0),glm::vec4(1.0, 0.3, 0.2, 1.0),"Sun");
	static GameObject earth(row::vector3(1.5e11, 0, 0), glm::vec3(0.5, 0.5, 0.5), 5.9722e24, row::vector3(0, 0, 29744),glm::vec4(0.3, 0.8, 0.9, 1.0),"Earth");
	static GameObject mars({ 2.2e11, 0, 0 }, glm::vec3(0.27, 0.27, 0.27), 2.4e24, { 0,0,24000 },glm::vec4(0.8, 0.5, 0.2, 1.0),"Mars");
	static GameObject mercury({ 5.0e10, 0, 0 }, { 0.14,0.14,0.14 }, 3.285e23, { 0, 0, 47000 }, glm::vec4(0.8, 0.8, 0.8, 1.0), "Mercury");
	static GameObject venus{ { 1.1e11, 0, 0 },{ 0.47,0.47,0.47 }, 4.8e24,{ 0, 0, 35000 },glm::vec4(0.68, 0.57, 0.12, 1.0), "Venus" };
	static GameObject jupiter{ { 7.7e11,0,0 },{5.6,5.6,5.6 }, 1e28,{ 0,0,13000 },glm::vec4(0.67, 0.57, 0.12, 1.0), "Jupiter" };
	static GameObject saturn{ { 1.4e12, 0, 0 },{4.7,4.7,4.7 }, 5.7e26,{ 0,0,9000 },glm::vec4(0.78, 0.67, 0.12, 1.0), "Saturn" };
	static GameObject uranus { { 2.8e12, 0, 0 }, {2.0,2.0,2.0 }, 8.7e25,{ 0, 0, 6835},glm::vec4(0.0,0.6,0.9,1.0), "Uranus" };
	static GameObject neptune { { 4.5e12, 0, 0 },{1.9,1.9,1.9 }, 1e26,{ 0,0,5477 },glm::vec4(0.0,0.5,0.8,1.0), "Neptune" };
	static GameObject pluto({ 7.3e12, 0, 0 }, {0.09,0.09,0.09 }, 1.3e22,{ 0,0,4748 },glm::vec4(0.8,0.7,0.4,1.0), "Pluto" );
}

#endif

