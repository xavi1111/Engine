#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL.h"
#include "glew.h"

typedef unsigned __int8 Uint8;

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init();
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	update_status Update() { return UPDATE_CONTINUE; }
	bool CleanUp() { return true; }
	GLuint vertex;
	GLuint fragment;

private:
	const Uint8* keyboard = NULL;
};
