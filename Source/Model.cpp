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
#include <string>

void Model::Load(const char* file_name)
{
	fbxPath = file_name;
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

void Model::DeleteCurrentModel()
{
	meshes.clear();
	materials.clear();
}

void Model::LoadMaterials(const aiScene* scene)
{
	aiString file;
	
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			LOG_ENGINE(file.data);
			GLuint texture = App->texture->Load(file.data);
			if (texture == NULL) 
			{
				std::string fbxStr = fbxPath.substr(0,fbxPath.find_last_of("/\\"));
				LOG_ENGINE("Aaaa:%s",fbxStr);
				std::string str = fbxStr.substr(fbxStr.find_last_of("/\\") + 1);
				std::string path = file.data;
				std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
				str.append(base_filename);
				texture = App->texture->Load(str);
				if (texture == NULL)
				{
					str = "..\\Source\\Textures\\";
					path = file.data;
					base_filename = path.substr(path.find_last_of("/\\") + 1);
					str.append(base_filename);
					texture = App->texture->Load(str);
				}
			}
			materials.push_back(texture);
			LOG_ENGINE("Loading materials");
		}
	}
}

void Model::LoadMeshes(aiMesh** currentMeshes, int numOfMeshes)
{
	for (unsigned i = 0; i < numOfMeshes; ++i)
	{
		Mesh* mesh = new Mesh();
		
		mesh->LoadVBO(currentMeshes[i]);
		mesh->LoadEBO(currentMeshes[i]);
		mesh->CreateVAO();
		mesh->material_index = currentMeshes[i]->mMaterialIndex;
		meshes.push_back(mesh);
	}
	LOG_ENGINE("Loading meshes");
}