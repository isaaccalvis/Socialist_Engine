#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init(JSON_Object* root_object);
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool Save(JSON_Object* root_object);
	bool Load(JSON_Object* root_object);

	void OnResize(int width, int height);

	SDL_GLContext GetContext() const;
	void SetContext(SDL_GLContext nContext);

private:
	SDL_GLContext context;

public:
	Light lights[MAX_LIGHTS];
	
	//math::float3x3 NormalMatrix;
	//math::float4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};