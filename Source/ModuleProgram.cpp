#include "Globals.h"
#include "SDL.h"
#include "glew.h"
#include "ModuleProgram.h"
#include "Application.h"
#include <filesystem>
#include <iostream>

using namespace std;



ModuleProgram::ModuleProgram()
{}

// Destructor
ModuleProgram::~ModuleProgram()
{}

bool ModuleProgram::Init()
{
	LOG_ENGINE("Init SDL Module Render");
	bool ret = true;
	SDL_Init(0);
	char* vertexData = LoadShaderSource("Game\\assets\\vertex.txt");
	vertex = CompileShader(GL_VERTEX_SHADER, vertexData);
	char* fragmentData = LoadShaderSource("Game\\assets\\shader.txt");
	fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentData);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG_ENGINE("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	return ret;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* source)
{
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			LOG_ENGINE("Log Info: %s", info);
			free(info);
		}
	}
	return shader_id;
}