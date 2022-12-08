#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRenderExercise.h"
#include "ModuleCamera.h"
#include "ModuleRender.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG_ENGINE("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG_ENGINE("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
			case SDL_DROPFILE:
				LOG_ENGINE(sdlEvent.drop.file)
				App->exercise->LoadModel(sdlEvent.drop.file);
			case SDL_MOUSEBUTTONDOWN:
				//if (sdlEvent.type == SDL_MOUSEMOTION)
					App->camera->MoveCamera(sdlEvent.motion.x, sdlEvent.motion.y);

				
        }
    }

    keyboard = SDL_GetKeyboardState(NULL);
	if (keyboard[SDL_SCANCODE_ESCAPE]) {
		return UPDATE_STOP;
	}
	else if (keyboard[SDL_SCANCODE_W]) {
		App->camera->SetPosition(0.0, 0.0, -0.01);
	}
	else if (keyboard[SDL_SCANCODE_S]) {
		App->camera->SetPosition(0.0, 0.0, 0.01);
	}
	else if (keyboard[SDL_SCANCODE_A]) {
		App->camera->SetPosition(-0.01, 0.0, 0.0);
	}
	else if (keyboard[SDL_SCANCODE_D]) {
		App->camera->SetPosition(0.01, 0.0, 0.0);
	}
	else if (keyboard[SDL_SCANCODE_Q]) {
		App->camera->SetPosition(0.0, -0.01, 0.0);
	}
	else if (keyboard[SDL_SCANCODE_E]) {
		App->camera->SetPosition(0.0, 0.01, 0.0);
	}
	
	
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG_ENGINE("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
