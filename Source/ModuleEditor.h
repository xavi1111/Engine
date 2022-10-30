#pragma once
#include "imgui.h"
#include "Module.h"


class ModuleEditor : public Module
{
public:
	void init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
};

