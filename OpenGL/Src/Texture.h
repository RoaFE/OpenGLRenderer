#pragma once

#include "Renderer.h"


class Texture
{
private:
	std::string m_FileDirectory;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& directory,const std::string& name);
	~Texture();


	void Active(unsigned int slot = 0) const;
	void Bind() const;
	void Bind(unsigned int slot) const;
	void Unbind() const;

	std::string m_FileName;
	unsigned int m_RendererID;
	std::string type;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};