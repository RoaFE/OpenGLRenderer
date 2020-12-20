#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"

#include "Font.h"

#include <string>

class Text
{
public:
	Text();
	~Text();

	void SetText(std::string text) { m_Text = text; }
	std::string GetText() { return m_Text; }
	void SetPos(glm::vec2 position) { m_Pos = position; }
	glm::vec2 GetPos() {return m_Pos;}
	void SetScale(float scale) { m_Scale = scale; }
	float GetScale() { return m_Scale; }
	void SetColour(glm::vec3 Colour) { m_Colour = Colour; }
	glm::vec3 GetColour() { return m_Colour; }
	void SetColour(float x,float y, float z) { m_Colour = glm::vec3(x,y,z); }
	void SetFont(Font font);
	Font GetFont() { return m_Font; }
	VertexArray* GetVAO() { return m_VAO; }
	VertexBuffer* GetVB() { return m_VB; }


	void Draw(Shader& shader);
	void Draw(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 colour);

	std::string m_Text;
	glm::vec2 m_Pos;
	glm::vec3 m_Colour;
	glm::mat4 m_LocalTransform;
	float m_Scale;

private:
	Font m_Font;

	VertexArray* m_VAO;
	VertexBuffer* m_VB;
};