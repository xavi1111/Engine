#pragma once
#include "Module.h"
#include "SDL.h"
#include "glew.h"
#include "Globals.h"
#include "DirectXTex.h"
class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	GLint internalFormat;
	GLint format;
	GLint type;
};


