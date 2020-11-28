#pragma once

#include <freetype/freetype.h>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <map>
#include "glm/glm.hpp"


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


private:
	FT_Library ft;
	FT_Face face;
	std::map<char, Character> Characters;
};




