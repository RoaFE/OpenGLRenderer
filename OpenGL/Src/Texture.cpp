#include "Texture.h"
#include "stb_image/stb_image.h"
Texture::Texture(const std::string& directory, const std::string& name)
	: m_RendererID(0), m_FileName(name), m_FileDirectory(directory), m_LocalBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load((directory + "/" + name).c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (m_LocalBuffer == NULL)
	{
		m_LocalBuffer = stbi_load((directory.substr(1,directory.length() - 1) + "/" + name).c_str(), &m_Width, &m_Height, &m_BPP, 4);
	}
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D,m_RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}


Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Active(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
}

void Texture::Bind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	Active(slot);
	Bind();
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
