#pragma once

#include "RenderObject.h"

class Plane : public RenderObject
{
public:
	Plane();

	Plane(vec3f pos);

	Plane(vec3f pos, vec3f rot, vec3f size, Material* material);

	float intersect(vec3f rayOrigin, vec3f rayDir);

	vec3f getNormal(vec3f hitPoint);
};

