#pragma once

#include "../Maths.h"

#define MIN_DEPTH 0.01f

typedef enum matType {
	DIFFUSE,
	REFLECTIVE,
	GLASS
} MaterialType;

typedef struct mat {
	vec3f colour;
	MaterialType type;
	float roughness;
	float emmisitivity;
	//Index of refraction
	float ior;

	mat() : colour(vec3f(0.8f, 0.8f, 0.8f)), type(MaterialType::DIFFUSE), emmisitivity(0.0f) {}

	mat(vec3f colour) : colour(colour), type(MaterialType::DIFFUSE), emmisitivity(0.0f) {}

	mat(vec3f colour, MaterialType type, float emmisitivity) : colour(colour), type(type), emmisitivity(emmisitivity) {}
} Material;

class RenderObject
{
public:
	vec3f pos, rot, size;

	RenderObject();

	RenderObject(vec3f pos);

	RenderObject(vec3f pos, vec3f rot, vec3f size, Material* material);

	MaterialType getType();

	Material* getMaterial();

	virtual float intersect(vec3f rayPos, vec3f rayDir) = 0;

	virtual vec3f getNormal(vec3f hitPoint) = 0;

	~RenderObject();
protected:

	Material* material;
};

