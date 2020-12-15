#include "Text.h"

Text::Text()
	:m_Colour(1,1,1),
	m_Scale(1.f),
	m_Pos(100,100),
	m_VAO(nullptr),
	m_VB(nullptr)
{
	m_VAO = new VertexArray;
	m_VB = new VertexBuffer(NULL, sizeof(float) * 6 * 4, GL_DYNAMIC_DRAW);
	VertexBufferLayout layout;
	layout.Push<float>(4);
	m_VAO->AddBuffer(*m_VB, layout);
}

Text::~Text()
{
}

void Text::SetFont(Font font)
{
	m_Font = font;
}

void Text::Draw(Shader & shader)
{
	shader.Bind();
	std::map<char, Character> Characters = m_Font.GetCharacters();
	shader.SetUniform3f("textColour", m_Colour.x, m_Colour.y, m_Colour.z);
	glActiveTexture(GL_TEXTURE0);
	m_VAO->Bind();
	glm::vec2 pos = m_Pos;
	// iterate through all characters
	std::string::const_iterator c;
	for (c = m_Text.begin(); c != m_Text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = pos.x + ch.Bearing.x * m_Scale;
		float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * m_Scale;

		float w = ch.Size.x * m_Scale;
		float h = ch.Size.y * m_Scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		m_VB->UpdateContent(vertices, sizeof(vertices));
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		pos.x += (ch.Advance >> 6) * m_Scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}

	m_VAO->Unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::Draw(Shader & shader, std::string text, float x, float y, float scale, glm::vec3 colour)
{
	shader.Bind();
	shader.SetUniform3f("textColour", colour.x, colour.y, colour.z);
	glActiveTexture(GL_TEXTURE0);
	m_VAO->Bind();
	// iterate through all characters
	std::map<char, Character> Characters = m_Font.GetCharacters();
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		m_VB->UpdateContent(vertices, sizeof(vertices));

		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	m_VAO->Unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}
