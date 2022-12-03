#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "Model.h"
#include "Mesh.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/material.h"
#include "assimp/mesh.h"

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", file_name, aiGetErrorString());
	}
}

void Model::LoadMaterials(const aiScene* scene)
{
	aiString file;
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->Load(file.data));
		}
	}
}

void Model::LoadMeshes(aiMesh** currentMeshes, int numOfMeshes)
{
	Mesh mesh;
	for (unsigned i = 0; i < numOfMeshes; ++i)
	{
		mesh.LoadVBO(currentMeshes[i]);
		mesh.LoadEBO(currentMeshes[i]);
		meshes.push_back(mesh);
	}
}