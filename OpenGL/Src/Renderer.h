#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Font.h"
#include <string>
#define ASSERT(x) if(!(x)) __debugbreak();
#ifdef DEBUG
	#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
	#define GLCall(x) x
#endif
void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
public:
	void Clear() const;
	void SetClearColour() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void DrawText(const Font& font, const Shader& shader, std::string text) const;
};