#pragma once
#include "Module.h"
#include "ModuleCamera.h"
#include "debugdraw.h"
#include "Frustum.h"
#include "SDL.h"
#include "glew.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	void SetFOV();
	void SetAspectRatio();
	void SetPlaneDistances();
	void SetPosition(float x, float y, float z);
	void SetOrientation();
	float4x4 GetView();
	float4x4 GetProjection();
	/*void LookAt(x, y, z);
	GetProjectionMatrix() OpenGL matrix order is different from default MathGeoLib!Math info here
	GetViewMatrix()*/

	Frustum frustum;
};

