#pragma once
#include "Globals.h"
#include "Application.h"
#include "assimp/cimport.h"
#include "assimp/mesh.h"
#include "SDL.h"
#include "glew.h"
#include <vector>

class Mesh
{
public:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);

	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	int material_index = 0;
	int num_vertices;
	int num_indices;
};

