#pragma once

#include <vector>

#include "RenderObjects/RenderObject.h"

#define PROBABILITY 1.0f / 3.141f

class World
{
public:
	World();

	void addRenderObject(RenderObject* obj);

	void render(vec3f rayOrigin, vec3f rayDir, int depth, vec3f& colour);

	~World();
private:
	std::vector<RenderObject*> renderables;

	RenderObject* intersect(vec3f rayOrigin, vec3f rayDir, float& dist);

	vec3f hemisphereSample(float a, float b);

	void ons(vec3f a, vec3f& b, vec3f& c);

	float getRand();
};

