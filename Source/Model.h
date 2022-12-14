#pragma once
#include "assimp/scene.h"
#include "Mesh.h"
#include "assimp/material.h"
#include "assimp/mesh.h"
#include "assimp/texture.h"
#include <vector>
#include <string>

class Model
{
public:
	void Load(const char* file_name);
	void LoadMaterials(const aiScene* scene);
	void LoadMeshes(aiMesh** meshes, int numOfMeshes);
	void DeleteCurrentModel();

	std::vector<Mesh*> meshes;
	std::vector<GLuint> materials;
	std::string fbxPath;
};

