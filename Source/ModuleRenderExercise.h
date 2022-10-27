#pragma once
#include "Module.h"
#include "SDL.h"
#include "glew.h"
#include "Globals.h"

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
	bool CleanUp() {return true;}

private:
	const Uint8* keyboard = NULL;
	GLuint program;
	GLuint vbo;
};