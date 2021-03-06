
#pragma once
#include "Color.h"
#include "MathGeoLib-1.5\src\MathGeoLib.h"

struct Light
{
	Light();

	void Init();
	void SetPos(float x, float y, float z);
	void Active(bool active);
	void Render();

	Color ambient;
	Color diffuse;
	math::float3 position;

	int ref;
	bool on;
};