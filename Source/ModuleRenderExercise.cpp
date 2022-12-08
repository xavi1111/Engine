#include "Globals.h"
#include "Application.h"
#include "SDL.h"
#include "glew.h"
#include "ModuleRenderExercise.h"
#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"
#include "Model.h"
#include "ModuleTexture.h"
#include "ModuleCamera.h"
#include "MathGeoLib.h"
#include "debugdraw.h"
#include "Frustum.h"


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
	modelClass.Load("Game\\assets\\BakerHouse.fbx");
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

// This function must be called each frame for drawing the matrix
void ModuleRenderExercise::RenderVBO(unsigned vbo, unsigned program)
{
	int height = 0;
	int width = 0;
	SDL_GetWindowSize(App->window->window, &width, &height);
	projection = App->camera->frustum.ProjectionMatrix();
	view = App->camera->frustum.ViewMatrix();
	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::identity,
		float3(2.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(0, 1, GL_TRUE, &projection[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3*2);
	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::Green);
	App->debugDraw->Draw(view, projection, width, height);	
}

void ModuleRenderExercise::LoadModel(char* path) 
{
	modelClass.DeleteCurrentModel();
	modelClass.Load(path);
}

update_status ModuleRenderExercise::Update()
{
	
	RenderVBO(vbo, program);
	for (int i = 0; i < modelClass.meshes.size(); i++) 
	{
		modelClass.meshes[i]->Draw(modelClass.materials);
	}
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}
