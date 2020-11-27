#include "Mesh.h"



Mesh::Mesh()
	:m_VAO(nullptr), m_VB(nullptr), m_IB(nullptr)
{
	

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

	unsigned int indices[] = {
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
	m_VB = new VertexBuffer(positions, 3 * 8 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);

	m_VAO->AddBuffer(*m_VB, layout);
	//index buffer object (ibo)
	m_IB = new IndexBuffer(indices, 36);
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
