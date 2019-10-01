#include "Application.h"
#include "ModuleTextures.h"

#include "mmgr/mmgr.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::SetBufferPos(unsigned int nBufferPos)
{
	this->BufferPos = nBufferPos;
}

void Texture::SetWidth(int nWidth)
{
	this->width = nWidth;
}

void Texture::SetHeigh(int nHeigh)
{
	this->heigh = nHeigh;
}

unsigned int Texture::GetBufferPos() const
{
	return BufferPos;
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeigh() const
{
	return heigh;
}

ModuleTextures::ModuleTextures(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "ModuleTextures";
}

bool ModuleTextures::CleanUp()
{
	textures.clear();

	if (last_texture != nullptr)
		delete last_texture;

	return true;
}

void ModuleTextures::AddTexture(Texture* texture)
{
	if (texture != nullptr)
	{
		textures.push_back(texture);
		// TODO: Treure que el last texture sigui assignat aqui
		last_texture = texture;
	}
}

void ModuleTextures::DeleteTexture(Texture* texture)
{
	for (std::list<Texture*>::iterator item = textures.end(); item != textures.begin();)
	{
		if ((*item) == texture)
		{
			item--;
			textures.erase(item++);
		}
	}
}