#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include <vector>

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
};



class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	VertexArray* GetVAO() { return m_VAO; };
	VertexBuffer* GetVB(){ return m_VB; };
	IndexBuffer* GetIB(){ return m_IB; };
	void CreateCube();
	void CreateQuad();
	void CreateSphere(float radius = 1.f, int longitude = 10, int latitutde = 10);

	void Draw(Shader &shader);

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;


protected:

	VertexArray* m_VAO;
	VertexBuffer* m_VB;
	IndexBuffer* m_IB;

	void SetupMesh();

};
