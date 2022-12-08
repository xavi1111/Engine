#pragma once
#include "Module.h"
#include "SDL.h"
#include "glew.h"
#include "Globals.h"
#include "DirectXTex.h"
#include <string>

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	GLuint Load(std::string data);
	void GetFormat();

	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	GLint internalFormat;
	GLint format;
	GLint type;
	GLuint texture;
};


