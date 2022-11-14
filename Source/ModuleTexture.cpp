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
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	std::string image = "..\\Source\\Test-image-Baboon.ppm";
	std::wstring wimage = std::wstring(image.begin(), image.end());
	result = LoadFromDDSFile(wimage.c_str(), DirectX::DDS_FLAGS_NONE, &md, img);
	if (FAILED(result))
	{
		result = LoadFromTGAFile(wimage.c_str(), &md, img);
		if (FAILED(result))
		{
			result = LoadFromWICFile(wimage.c_str(), DirectX::WIC_FLAGS_NONE, &md, img);
			if (FAILED(result))
			{
				LOG("No texture loaded--------------");
			}
		}
	}

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, result);
	//glTexImage2D(GL_TEXTURE_2D, md.mipLevels, md.format, 1, 1, 0, , metaData., metaData.);
	glActiveTexture(GL_TEXTURE_2D);
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