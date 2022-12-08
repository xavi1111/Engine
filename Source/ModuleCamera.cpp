#include "ModuleCamera.h"
#include "debugdraw.h"
#include "Frustum.h"
#include "SDL.h"
#include "glew.h"
#include "ModuleWindow.h"
#include "Application.h"



ModuleCamera::ModuleCamera()
{}

// Destructor
ModuleCamera::~ModuleCamera()
{}

bool ModuleCamera::Init()
{
	int height = 0;
	int width = 0;
	SDL_GetWindowSize(App->window->window, &width, &height);
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetPos(float3(0, 3, 5));
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio((pi / 180) * 90.0f, width / height);
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

void ModuleCamera::SetFOV() 
{
	//frustum->SetHorizontalFovAndAspectRatio(float, float);
}
void ModuleCamera::SetAspectRatio()
{
	//frustum->SetHorizontalFovAndAspectRatio(FLOAT, FLOAT);
}
void ModuleCamera::SetPlaneDistances()
{
	//frustum->SetViewPlaneDistances(FLOAT, FLOAT);
}
void ModuleCamera::SetPosition(float x, float y, float z)
{
	frustum.SetPos(float3(frustum.Pos().x + x, frustum.Pos().y + y, frustum.Pos().z + z));
}
void ModuleCamera::SetOrientation()
{
}
void ModuleCamera::MoveCamera(float x, float y)
{

}
float4x4 ModuleCamera::GetView()
{
	return frustum.ViewMatrix();
}
float4x4 ModuleCamera::GetProjection()
{
	return frustum.ProjectionMatrix();
}
