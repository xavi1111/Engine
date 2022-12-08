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
	return true;
}

update_status ModuleTexture::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}
update_status ModuleTexture::Update()
{

	return UPDATE_CONTINUE;
}
update_status ModuleTexture::PostUpdate()
{
	return UPDATE_CONTINUE;
}

GLuint ModuleTexture::Load(std::string data)
{
	bool error = false;
	HRESULT result = E_FAIL;
	std::wstring wimage = std::wstring(data.begin(), data.end());
	LOG_ENGINE("Path: %s", wimage);
	result = LoadFromDDSFile(wimage.c_str(), DirectX::DDS_FLAGS_NONE, &md, img);
	if (FAILED(result))
	{
		LOG_ENGINE("No DDS texture loaded--------------");
		result = LoadFromTGAFile(wimage.c_str(), &md, img);
		if (FAILED(result))
		{
			LOG_ENGINE("No TGA texture loaded--------------");
			result = LoadFromWICFile(wimage.c_str(), DirectX::WIC_FLAGS_NONE, &md, img);
			if (FAILED(result))
			{
				LOG_ENGINE("No WIC texture loaded--------------");
				error = true;
			}
		}
	}
	if (!error) {
		DirectX::ScratchImage imgAux;
		const DirectX::Image* image = img.GetImage(0, 0, 0);
		result = FlipRotate(*image, DirectX::TEX_FR_FLIP_VERTICAL, imgAux);
		if (FAILED(result))
		{
			LOG_ENGINE("Rotation failed--------------");
		}
		else
		{
			LOG_ENGINE("Rotation OK--------------");
		}
		GetFormat();
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, md.height, md.width, 0, format, type, imgAux.GetPixels());
		glGenerateMipmap(GL_TEXTURE_2D);
		return texture;
	}
	return NULL;
}

void ModuleTexture::GetFormat() 
{
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
}