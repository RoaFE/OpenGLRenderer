#include "Camera.h"



Camera::Camera()
	: m_Position(0,0,10),m_Direction(0,0,-1),m_Right(1,0,0),m_Up(0,1,0),m_FoV(m_InitialFoV),m_MouseOrigin(960/2,540/2)
{
}


Camera::~Camera()
{
}


void Camera::UpdateOrientation(float dt ,GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window,m_MouseOrigin.x,m_MouseOrigin.y);
	m_HorizontalAngle += m_MouseSpeed * dt * float(m_MouseOrigin.x - xpos);
	m_VerticalAngle += m_MouseSpeed * dt * float(m_MouseOrigin.y - ypos);

	m_Direction = glm::vec3(cos(m_VerticalAngle) * sin(m_HorizontalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle));

	m_Right = glm::vec3(
		sin(m_HorizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_HorizontalAngle - 3.14f / 2.0f)
	);

	m_Up = glm::cross(m_Right, m_Direction);
}

void Camera::UpdatePosition(float dt, GLFWwindow* window)
{
	float speed = m_Speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = m_Speed * 10;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_Position += m_Direction * dt * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_Position -= m_Direction * dt * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_Position += m_Right * dt * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_Position -= m_Right * dt * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		m_Position += glm::vec3(0, 1, 0) * dt * speed;
	}	
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		m_Position -= glm::vec3(0,1,0) * dt * speed;
	}
}

void Camera::UpdateMatrices(float dt)
{
	m_Proj = glm::perspective(glm::radians(m_FoV), 960.f / 540.f, 0.1f, 1000.f);
	m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
}
