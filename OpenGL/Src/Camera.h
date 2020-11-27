#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <GLFW/glfw3.h>


class Camera
{
public:
	Camera();
	~Camera();

	void UpdateOrientation(float dt,GLFWwindow* window);
	void UpdatePosition(float dt, GLFWwindow* window);
	void UpdateMatrices(float dt);
	void SetFoV(float FoV) { m_FoV = FoV; }
	void SetMouseOrigin(glm::vec2 mousePos) { m_MouseOrigin = mousePos; }
	glm::mat4 GetProj() { return m_Proj; }
	glm::mat4 GetView() { return m_View; }

	void SetPos(float x, float y, float z) { m_Position = glm::vec3(x, y, z); }
	void SetPos(glm::vec3 pos) { m_Position = pos; }
	glm::vec3 GetDirection() { return m_Direction; };

protected:
	// position
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	glm::vec2 m_MouseOrigin;
	// horizontal angle : toward -Z
	float m_HorizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	float m_VerticalAngle = 0.0f;
	// Initial Field of View
	float m_InitialFoV = 45.0f;
	float m_FoV;
	float m_Speed = 3.0f; // 3 units / second
	float m_MouseSpeed = 0.1f;

	glm::mat4 m_Proj, m_View;
};

