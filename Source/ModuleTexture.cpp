#include "ModuleTexture.h"
#include "SDL.h"
#include "glew.h"
#include "Globals.h"
#include "DirectXTex.h"
#include <string>

ModuleTexture::ModuleTexture()
{}

// Destructor
ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Init()
{
	HRESULT result = E_FAIL;
	
	std::string image = "..\\Source\\Test-image-Baboon.ppm";
	std::wstring wimage = std::wstring(image.begin(), image.end());
	result = LoadFromDDSFile(wimage.c_str(), DirectX::DDS_FLAGS_NONE, &md, img);
	if (FAILED(result))
	{
		LOG("No texture loaded--------------");
		result = LoadFromTGAFile(wimage.c_str(), &md, img);
		if (FAILED(result))
		{
			LOG("No texture loaded--------------");
			result = LoadFromWICFile(wimage.c_str(), DirectX::WIC_FLAGS_NONE, &md, img);
			if (FAILED(result))
			{
				LOG("No texture loaded--------------");
			}
		}
	}

	glActiveTexture(GL_TEXTURE5);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE5, texture);
	
	switch (md.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}

	
	return true;
}

update_status ModuleTexture::PreUpdate()
{
	return UPDATE_CONTINUE;
}
update_status ModuleTexture::Update()
{
	glTexImage2D(GL_TEXTURE5, 0, internalFormat, md.height, md.width, 0, format, type, img.GetPixels());
	glGenerateMipmap(GL_TEXTURE5);
	glActiveTexture(GL_TEXTURE5);
	return UPDATE_CONTINUE;
}
update_status ModuleTexture::PostUpdate()
{
	return UPDATE_CONTINUE;
}