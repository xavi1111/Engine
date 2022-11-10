#pragma once
#include "Module.h"
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
	void SetPosition();
	void SetOrientation();
	/*void LookAt(x, y, z);
	GetProjectionMatrix() OpenGL matrix order is different from default MathGeoLib!Math info here
	GetViewMatrix()*/
};

