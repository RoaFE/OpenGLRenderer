#include "Mesh.h"



int coordToIndice(int x, int y, int width)
{
	return x + (y * width);
}

Mesh::Mesh()
	:m_VAO(nullptr), m_VB(nullptr), m_IB(nullptr), m_Setup(false)
{
	

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	:m_VAO(nullptr), m_VB(nullptr), m_IB(nullptr), m_Setup(false)
{
	m_Vertices = vertices;
	m_Indices = indices;

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures)
{
	m_Textures = textures;

	m_Vertices = vertices;
	m_Indices = indices;
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
	vertex.TexCoords = glm::vec2(0.f, 0.f);
	m_Vertices.push_back(vertex);
	// 6	Back top right
	vertex.Position = glm::vec3(1.f, 1.f, -1.0f);
	vertex.Normal = glm::vec3(1.f, 1.f, -1.0f);
	vertex.TexCoords = glm::vec2(1.f, 0.f);
	m_Vertices.push_back(vertex);
	// 7	Back top left
	vertex.Position = glm::vec3(-1.f, 1.f, -1.0f);
	vertex.Normal = glm::vec3(-1.f, 1.f, -1.0f);
	vertex.TexCoords = glm::vec2(1.f, 1.f);
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

void Mesh::CreatePlane(int width, int height)
{
	int heightVert = height + 1;
	int widthVert = width + 1;
	
	//float halfHeightVert = heightVert / 2.f;
	//float halfWidthVert = widthVert / 2.f;


	for (int z = 0; z < heightVert; z++)
	{
		for (int x = 0; x < widthVert; x++)
		{
			Vertex vertex;
			vertex.TexCoords = glm::vec2((float)x/(float)widthVert,(float)z/(float)heightVert);
			vertex.Normal = glm::vec3(0,1,0);
			vertex.Position = glm::vec3(x,0,z);
			m_Vertices.push_back(vertex);
		}
	}

	for (int z = 0; z < heightVert - 1; z++)
	{
		for (int x = 0; x < widthVert - 1; x++)
		{
			if ((x + z) % 2)
			{
				m_Indices.push_back(coordToIndice(x, z, widthVert));
				m_Indices.push_back(coordToIndice(x, z + 1, widthVert));
				m_Indices.push_back(coordToIndice(x + 1, z, widthVert));

				m_Indices.push_back(coordToIndice(x + 1, z, widthVert));
				m_Indices.push_back(coordToIndice(x, z + 1, widthVert));
				m_Indices.push_back(coordToIndice(x + 1, z + 1, widthVert));
			}
			else
			{
				m_Indices.push_back(coordToIndice(x, z, widthVert));
				m_Indices.push_back(coordToIndice(x, z + 1, widthVert));
				m_Indices.push_back(coordToIndice(x + 1, z + 1, widthVert));

				m_Indices.push_back(coordToIndice(x + 1, z, widthVert));
				m_Indices.push_back(coordToIndice(x, z, widthVert));
				m_Indices.push_back(coordToIndice(x + 1, z + 1, widthVert));
			}


		}
	}

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
	//calculating increment of angle in long and latitude
	float theta = (2 * 3.14159) / lat;
	float delta = 3.14159 / lon;
	int index = 0;
	Vertex vertex;
	for (float i = 0; i < lon; i++)
	{
		for (float o = 0; o < lat; o++)
		{

			//Tex cordinates are calcualted since the circle is 
			//like a rectangle curved into a sphere
			vertex.TexCoords = glm::vec2((theta * o / (2 * 3.14151)), delta * i / 3.14151);
			//normals are the exact same as the vector from the centre to that vertice
			vertex.Normal = glm::vec3(cos(theta * o) * sin(delta * i), cos(delta * i), sin(theta * o) * sin(delta * i));
			//vertex cordinates 
			vertex.Position = glm::vec3(r * cos(theta * o) * sin(delta * i), r * cos(delta * i), r * sin(theta * o) * sin(delta * i));

			m_Vertices.push_back(vertex);

			//like a rectangle curved into a sphere
			vertex.TexCoords = glm::vec2((theta * o / (2 * 3.14151)), delta * ((i + 1)) / 3.14151);
			//normals are the exact same as the vector from the centre to that vertice
			vertex.Normal = glm::vec3(cos(theta * o) * sin(delta * ((i + 1))), cos(delta * ((i + 1))), sin(theta * o) * sin(delta * ((i + 1))));
			//vertex cordinates 
			vertex.Position = glm::vec3(r * cos(theta * o) * sin(delta * ((i + 1))), r * cos(delta * ((i + 1))), r * sin(theta * o) * sin(delta * ((i + 1))));

			m_Vertices.push_back(vertex);

			//like a rectangle curved into a sphere
			vertex.TexCoords = glm::vec2(theta * ((o + 1)) / (2 * 3.14151), delta * (i + 1) / 3.14151);
			//normals are the exact same as the vector from the centre to that vertice
			vertex.Normal = glm::vec3(cos(theta * ((o + 1))) * sin(delta * (i + 1)), cos(delta * (i + 1)), sin(theta * ((o + 1))) * sin(delta * (i + 1)));
			//vertex cordinates 
			vertex.Position = glm::vec3(r * cos(theta * ((o + 1))) * sin(delta * (i + 1)), r * cos(delta * (i + 1)), r * sin(theta * ((o + 1))) * sin(delta * (i + 1)));

			m_Vertices.push_back(vertex);

			//like a rectangle curved into a sphere
			vertex.TexCoords = glm::vec2(theta * (o + 1) / (2 * 3.14151), delta * i / 3.14151);
			//normals are the exact same as the vector from the centre to that vertice
			vertex.Normal = glm::vec3(cos(theta * (o + 1)) * sin(delta * i), cos(delta * i), sin(theta * (o + 1)) * sin(delta * i));
			//vertex cordinates 
			vertex.Position = glm::vec3(r * cos(theta * (o + 1)) * sin(delta * i), r * cos(delta * i), r * sin(theta * (o + 1)) * sin(delta * i));

			m_Vertices.push_back(vertex);

			m_Indices.push_back(index + 2);
			m_Indices.push_back(index + 1);
			m_Indices.push_back(index);

			m_Indices.push_back(index + 2);
			m_Indices.push_back(index);
			m_Indices.push_back(index + 3);
			index += 4;


		}
	}

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

void Mesh::Draw(Shader & shader)
{
	if (!m_Setup)
		SetupMesh();
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i]->Active(i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = m_Textures[i]->type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
			name = "material.diffuse";
		}
		else if (name == "texture_specular") {
			number = std::to_string(specularNr++); // transfer unsigned int to stream
			name = "material.specular";
		}
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

		shader.SetUniform1f((name + number).c_str(), i);
		m_Textures[i]->Bind();
	}

	// draw mesh
	m_VAO->Bind();
	m_IB->Bind();
	glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, 0);
	m_IB->Unbind();
	m_VAO->Unbind();

	//glActiveTexture(GL_TEXTURE0);
}

void Mesh::Destroy()
{
	for (Texture* texture : m_Textures)
	{
		//texture memory should have been deleted in loaded textures in model
		if (texture)
		{
			texture = nullptr;
		}
		m_Textures.clear();
	}
}

void Mesh::SetupMesh()
{
	m_Setup = true;
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
