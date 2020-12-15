#pragma once

#include <freetype/freetype.h>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <map>
#include "glm/glm.hpp"
#include "Shader.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};


class Font
{
public:
	Font();
	~Font();

	bool LoadFont(std::string path);
	void SetFontSize(float size);

	void RenderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 colour);
	std::map<char, Character> GetCharacters() { return Characters; }


private:
	FT_Library ft;
	FT_Face face;
	std::map<char, Character> Characters;


	unsigned int VAO, VBO;

	VertexArray* m_VAO;
	VertexBuffer* m_VB;
	IndexBuffer* m_IB;
};




