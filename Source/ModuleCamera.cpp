#include "ModuleCamera.h"

ModuleCamera::ModuleCamera()
{}

// Destructor
ModuleCamera::~ModuleCamera()
{}

bool ModuleCamera::Init()
{
	return true;
}

update_status ModuleCamera::PreUpdate() 
{
	return UPDATE_CONTINUE;
}
update_status ModuleCamera::Update() 
{
	return UPDATE_CONTINUE;
}
update_status ModuleCamera::PostUpdate() 
{
	return UPDATE_CONTINUE;
}
