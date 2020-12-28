#pragma once
#include "Assimp/Importer.hpp"
#include "Assimp/scene.h"
#include "Assimp/postprocess.h"

#include "Shader.h"
#include "Mesh.h"

#include <vector>
#include <string>
#include <iostream>

class Model
{
public:
	Model(const char *path)
	{
		loadModel(path);
	}
	void Draw(Shader &shader);

	void Destroy();

private:
	// model data
	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture*> textures_loaded;

	void loadModel(std::string path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};