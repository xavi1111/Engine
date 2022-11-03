#include "Globals.h"
#include "Application.h"
#include "SDL.h"
#include "glew.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "MathGeoLibFwd.h"

ModuleRenderExercise::ModuleRenderExercise()
{}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{}

bool ModuleRenderExercise::Init()
{
	bool ret = true;
	SDL_Init(0);
	program = CreateProgram(App->program->vertex, App->program->fragment);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLfloat vertices[] = { -1, -1, 0,  1, -1, 0,  0, 1, 0 };
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
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
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);
	float4x4 model, view, projection;

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);

	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
}

update_status ModuleRenderExercise::Update()
{
	RenderVBO(vbo, program);
	return UPDATE_CONTINUE;
}
