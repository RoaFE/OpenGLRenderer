#include "Mesh.h"



Mesh::Mesh()
	:m_VAO(nullptr), m_VB(nullptr), m_IB(nullptr)
{
	

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	:m_VAO(nullptr), m_VB(nullptr), m_IB(nullptr)
{
	m_Vertices = vertices;
	m_Indices = indices;

	SetupMesh();
}

Mesh::~Mesh()
{
	if (m_VAO)
	{
		delete m_VAO;
		m_VAO = nullptr;
	}

	if (m_IB)
	{
		delete m_IB;
		m_IB = nullptr;
	}

	if (m_VB)
	{
		delete m_VB;
		m_VB = nullptr;
	}
}

void Mesh::CreateCube()
{
	Vertex vertex;
	// 0	Front bottom left
	vertex.Position = glm::vec3(-1.f, -1.f, 1.0f);
	vertex.Normal = glm::vec3(-1.f, -1.f, 1.0f);
	vertex.TexCoords = glm::vec2(0.f, 1.f);
	m_Vertices.push_back(vertex);
	// 1	Front bottom right
	vertex.Position = glm::vec3(1.f, -1.f, 1.0f);
	vertex.Normal = glm::vec3(1.f, -1.f, 1.0f);
	vertex.TexCoords = glm::vec2(1.f, 1.f);
	m_Vertices.push_back(vertex);
	// 2	Front top right
	vertex.Position = glm::vec3(1.f, 1.f, 1.0f);
	vertex.Normal = glm::vec3(1.f, 1.f, 1.0f);
	vertex.TexCoords = glm::vec2(1.f, 0.f);
	m_Vertices.push_back(vertex);
	// 3	Front top left
	vertex.Position = glm::vec3(-1.f, 1.f, 1.0f);
	vertex.Normal = glm::vec3(-1.f, 1.f, 1.0f);
	vertex.TexCoords = glm::vec2(0.f, 0.f);
	m_Vertices.push_back(vertex);
	// 4	Back bottom left
	vertex.Position = glm::vec3(-1.f, -1.f, -1.0f);
	vertex.Normal = glm::vec3(-1.f, -1.f, -1.0f);
	vertex.TexCoords = glm::vec2(0.f, 1.f);
	m_Vertices.push_back(vertex);
	// 5	Back bottom right
	vertex.Position = glm::vec3(1.f, -1.f, -1.0f);
	vertex.Normal = glm::vec3(1.f, -1.f, -1.0f);
	vertex.TexCoords = glm::vec2(1.f, 1.f);
	m_Vertices.push_back(vertex);
	// 6	Back top right
	vertex.Position = glm::vec3(1.f, 1.f, -1.0f);
	vertex.Normal = glm::vec3(1.f, 1.f, -1.0f);
	vertex.TexCoords = glm::vec2(1.f, 0.f);
	m_Vertices.push_back(vertex);
	// 7	Back top left
	vertex.Position = glm::vec3(-1.f, 1.f, -1.0f);
	vertex.Normal = glm::vec3(-1.f, 1.f, -1.0f);
	vertex.TexCoords = glm::vec2(0.f, 0.f);
	m_Vertices.push_back(vertex);


	float positions[] = {
		-1.f, -1.f,  1.0f,	// 0	Front bottom left
		 1.f, -1.f,  1.0f,	// 1	Front bottom right
		 1.f,  1.f,  1.0f, 	// 2	Front top right
		-1.f,  1.f,  1.0f,	// 3	Front top left
		-1.f, -1.f, -1.0f,	// 4	Back bottom left
		 1.f, -1.f, -1.0f,	// 5	Back bottom right
		 1.f,  1.f, -1.0f, 	// 6	Back top right
		-1.f,  1.f, -1.0f,	// 7	Back top left
	};

	m_Indices = {
		0, 1, 2,
		2, 3, 0,	//Front Face
		1, 5, 6,
		6, 2, 1,	//Right Face
		4, 0, 3,
		3, 7, 4,	//Left Face
		3, 2, 6,
		6, 7, 3,	//Top Face
		0, 4, 5,
		5, 1, 0,	//Bottom Face
		4, 7, 6,
		6, 5, 4		//Back Face
	};

	m_VAO = new VertexArray;
	m_VB = new VertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VB, layout);
	//index buffer object (ibo)
	m_IB = new IndexBuffer(m_Indices.data(), m_Indices.size());
}

void Mesh::CreateQuad()
{
	Vertex vertex;
	// 0	Front bottom left
	vertex.Position = glm::vec3(-1.f, -1.f, 1.0f);
	vertex.Normal = glm::vec3(0.f, 0.f, 1.0f);
	vertex.TexCoords = glm::vec2(0.f, 1.f);
	m_Vertices.push_back(vertex);
	// 1	Front bottom right
	vertex.Position = glm::vec3(1.f, -1.f, 1.0f);
	vertex.TexCoords = glm::vec2(1.f, 1.f);
	m_Vertices.push_back(vertex);
	// 2	Front top right
	vertex.Position = glm::vec3(1.f, 1.f, 1.0f);
	vertex.TexCoords = glm::vec2(1.f, 0.f);
	m_Vertices.push_back(vertex);
	// 3	Front top left
	vertex.Position = glm::vec3(-1.f, 1.f, 1.0f);
	vertex.TexCoords = glm::vec2(0.f, 0.f);
	m_Vertices.push_back(vertex);


	m_Indices = { 0, 1, 2, 2, 3, 0 };

	m_VAO = new VertexArray;
	m_VB = new VertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VB, layout);
	//index buffer object (ibo)
	m_IB = new IndexBuffer(m_Indices.data(), m_Indices.size());

}

void Mesh::CreateSphere(float r, int lon, int lat)
{
	std::vector<float> vertex;
	std::vector<int> indices;
	//calculating increment of angle in long and latitude
	float theta = (2 * 3.14159) / lat;
	float delta = 3.14159 / lon;
	int index = 0;
	for (float i = 0; i < lon; i++)
	{
		for (float o = 0; o < lat; o++)
		{


			////Tex cordinates are calcualted since the circle is 
			////like a rectangle curved into a sphere
			//texCoords.push_back(theta*o / (2 * 3.14151));
			//texCoords.push_back(delta*i / 3.14151);
			////normals are the exact same as the vector from the centre to that vertice
			//normals.push_back(cos(theta*o) * sin(delta*i));
			//normals.push_back(cos(delta * i));
			//normals.push_back(sin(theta*o) * sin(delta*i));
			//vertex cordinates 
			vertex.push_back(r*cos(theta*o) * sin(delta*i));
			vertex.push_back(r*cos(delta * i));
			vertex.push_back(r*sin(theta*o) * sin(delta*i));

			//texCoords.push_back(theta*o / (2 * 3.14151));
			//texCoords.push_back(delta*((i + 1)) / 3.14151);
			//normals.push_back(cos(theta*o) * sin(delta*((i + 1))));
			//normals.push_back(cos(delta * ((i + 1))));
			//normals.push_back(sin(theta*o) * sin(delta*((i + 1))));
			vertex.push_back(r*cos(theta*o) * sin(delta*((i + 1))));
			vertex.push_back(r*cos(delta * ((i + 1))));
			vertex.push_back(r*sin(theta*o) * sin(delta*((i + 1))));


			//texCoords.push_back(theta*((o + 1)) / (2 * 3.14151));
			//texCoords.push_back(delta*(i + 1) / 3.14151);
			//normals.push_back(cos(theta*((o + 1))) * sin(delta*(i + 1)));
			//normals.push_back(cos(delta * (i + 1)));
			//normals.push_back(sin(theta*((o + 1))) * sin(delta*(i + 1)));
			vertex.push_back(r*cos(theta*((o + 1))) * sin(delta*(i + 1)));
			vertex.push_back(r*cos(delta * (i + 1)));
			vertex.push_back(r*sin(theta*((o + 1))) * sin(delta*(i + 1)));


			//texCoords.push_back(theta*(o + 1) / (2 * 3.14151));
			//texCoords.push_back(delta*i / 3.14151);
			//normals.push_back(cos(theta*(o + 1)) * sin(delta*i));
			//normals.push_back(cos(delta * i));
			//normals.push_back(sin(theta*(o + 1)) * sin(delta*i));
			vertex.push_back(r*cos(theta*(o + 1)) * sin(delta*i));
			vertex.push_back(r*cos(delta * i));
			vertex.push_back(r*sin(theta*(o + 1)) * sin(delta*i));
			indices.push_back(index + 2);
			indices.push_back(index + 1);
			indices.push_back(index);

			indices.push_back(index + 2);
			indices.push_back(index);
			indices.push_back(index + 3);
			index += 4;


		}
	}

	m_VAO = new VertexArray;
	m_VB = new VertexBuffer(vertex.data(), vertex.size() * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);

	m_VAO->AddBuffer(*m_VB, layout);
	//index buffer object (ibo)
	m_IB = new IndexBuffer(indices.data(), indices.size());
}

void Mesh::Draw(Shader & shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	//for (unsigned int i = 0; i < textures.size(); i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
	//	// retrieve texture number (the N in diffuse_textureN)
	//	std::string number;
	//	std::string name = textures[i].type;
	//	if (name == "texture_diffuse")
	//		number = std::to_string(diffuseNr++);
	//	else if (name == "texture_specular")
	//		number = std::to_string(specularNr++);

	//	shader.SetUniform1f(("material." + name + number).c_str(), i);
	//	glBindTexture(GL_TEXTURE_2D, textures[i].id);
	//}
	//glActiveTexture(GL_TEXTURE0);

	// draw mesh
	m_VAO->Bind();
	m_IB->Bind();
	glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, 0);
	m_IB->Unbind();
	m_VAO->Unbind();
}

void Mesh::SetupMesh()
{
	m_VAO = new VertexArray;
	m_VB = new VertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VB, layout);
	//index buffer object (ibo)
	m_IB = new IndexBuffer(m_Indices.data(), m_Indices.size());
}
