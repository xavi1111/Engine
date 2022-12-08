#pragma once
#include "Module.h"
#include "Model.h"
#include "SDL.h"
#include "glew.h"
#include "Globals.h"
#include "float4x4.h"

typedef unsigned __int8 Uint8;

class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
	void RenderVBO(unsigned vbo, unsigned program);
	update_status Update();
	update_status PostUpdate();
	bool CleanUp() {return true;}
	GLuint program;

private:
	const Uint8* keyboard = NULL;
	GLuint vbo;
	float4x4 model, view, projection;
	Model modelClass;
};