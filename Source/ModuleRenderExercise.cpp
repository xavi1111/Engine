#include "Globals.h"
#include "Application.h"
#include "SDL.h"
#include "glew.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"

ModuleRenderExercise::ModuleRenderExercise()
{}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{}

bool ModuleRenderExercise::Init()
{
	LOG("Init SDL Module Render");
	bool ret = true;
	SDL_Init(0);
	program = CreateProgram(App->program->vertex, App->program->fragment);
	glGenBuffers(1, &vbo);
	LOG("Error1: %i\n", glGetError());
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	LOG("Error2: %i\n", glGetError());
	GLfloat vertices[] = { -1, -1, 0,  1, -1, 0,  0, 1, 0 };
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
	LOG("Error3: %i\n", glGetError());
	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}



unsigned ModuleRenderExercise::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	unsigned program_id = glCreateProgram();
	glAttachShader(program_id, vtx_shader);
	glAttachShader(program_id, frg_shader);
	glLinkProgram(program_id);
	int res;
	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(program_id, len, &written, info);
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return program_id;
}

// This function must be called each frame for drawing the triangle
void ModuleRenderExercise::RenderVBO(unsigned vbo, unsigned program)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	LOG("Error4: %i\n", glGetError());
	glEnableVertexAttribArray(0);
	LOG("Error5: %i\n", glGetError());
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	LOG("Error6: %i\n", glGetError());
	glUseProgram(program);
	LOG("Error7: %i\n", glGetError());
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
	LOG("Error8: %i\n", glGetError());
	
}

update_status ModuleRenderExercise::Update()
{
	RenderVBO(vbo, program);
	return update_status();
}
