#include "Renderer.h"

#include <iostream>


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}


void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::DrawLine(Shader& shader, glm::vec3 start, glm::vec3 end, glm::vec4 colour, float width)
{
	shader.SetUniform4f("u_Colour",colour.x, colour.y, colour.z, colour.w);
	shader.Bind();
	glBegin(GL_LINES);
	glLineWidth((GLfloat)width);
	glVertex3f(start.x, start.y, start.z);
	glVertex3f(end.x, end.y, end.z);
	glEnd();
	glLineWidth(1.0f);
}


