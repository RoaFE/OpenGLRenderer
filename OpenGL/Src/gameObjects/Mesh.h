#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	VertexArray* GetVAO() { return m_VAO; };
	VertexBuffer* GetVB(){ return m_VB; };
	IndexBuffer* GetIB(){ return m_IB; };
	void CreateCube();
	void CreateSphere(float radius = 1.f, int longitude = 10, int latitutde = 10);
protected:

	VertexArray* m_VAO;
	VertexBuffer* m_VB;
	IndexBuffer* m_IB;

};
