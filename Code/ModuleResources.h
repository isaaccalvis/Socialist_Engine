#ifndef __ModuleResources_H__
#define __ModuleResources_H__

#include <vector>
#include "Module.h"

#include "Mesh.h"
#include "Texture.h"

class ResourceMesh
{
public:
	ResourceMesh(Mesh* mesh, uuid_unit uuid);
	~ResourceMesh();
public:
	Mesh* mesh = nullptr;
	uuid_unit uuid = 0;
	unsigned int totalInUse = 0;
	std::string name;
};

class ResourceMaterial
{
public:
	ResourceMaterial(Texture* texture, uuid_unit uuid);
	~ResourceMaterial();
public:
	Texture* texture = nullptr;
	uuid_unit uuid = 0;
	unsigned int totalInUse;
	std::string name;
};

class ModuleResources : public Module
{
public:
	// Module Resources
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();
	bool CleanUp();

	// Meshes
	void			AddResourceMesh(Mesh* mesh, uuid_unit uuid);
	void			DeleteResourceMesh(uuid_unit uuid);
	ResourceMesh*	GetResourceMesh(uuid_unit uuid);
	ResourceMesh*	GetResourceMesh(std::string name);
	void			CleanResourceMeshes();

	// Materials
	void				AddResourceMaterial(Texture* texture, uuid_unit uuid);
	void				DeleteResourceMaterial(uuid_unit uuid);
	ResourceMaterial*	GetResourceMaterial(uuid_unit uuid);
	ResourceMaterial*	GetResourceMaterial(std::string name);
	void				CleanResourceMaterial();

public:
	std::vector<ResourceMesh*>		resourcesMesh;
	std::vector<ResourceMaterial*>	resourceMaterial;
};

#endif