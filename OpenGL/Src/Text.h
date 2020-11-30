#pragma once
#include "Text.h"
#include "glm/common.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"

#include <string>

class Text
{
public:
	Text();
	~Text();

	void SetText(std::string text) { m_Text = text; }
	void SetPos(glm::vec2 position) { m_Pos = position;}
	void SetScale(float scale) { m_Scale = scale; }
	void SetColour(glm::vec3 Colour) { m_Colour = Colour; }
	void SetColour(float x,float y, float z) { m_Colour = glm::vec3(x,y,z); }



private:

	std::string m_Text;
	glm::vec2 m_Pos;
	glm::vec3 m_Colour;
	float m_Scale;


	VertexArray* m_VAO;
	VertexBuffer* m_VB;
};