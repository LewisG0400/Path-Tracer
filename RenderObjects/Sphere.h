#pragma once

#include "RenderObject.h"

#include <stdio.h>

class Sphere : public RenderObject
{
public:

	Sphere();

	Sphere(vec3f pos);

	Sphere(vec3f pos, vec3f rot, vec3f size, Material* material);

	float intersect(vec3f rayPos, vec3f rayDir);

	vec3f getNormal(vec3f hitPoint);

	~Sphere();
private:
};

