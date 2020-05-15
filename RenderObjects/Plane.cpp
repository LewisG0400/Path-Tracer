#include "Plane.h"

Plane::Plane() {
	pos = vec3f(0.0f, 0.0f, -3.0f);
	rot = vec3f(0.0f, 0.0f, 0.0f);
	size = vec3f(1.0f, 1.0f, 1.0f);
	material = new Material();
}

Plane::Plane(vec3f pos) {
	this->pos = pos;
	rot = vec3f(0.0f, 0.0f, 0.0f);
	size = vec3f(1.0f, 1.0f, 1.0f);
	material = new Material();
	material->colour = vec3f(0.1f, 0.2f, 0.7f);
}

Plane::Plane(vec3f pos, vec3f rot, vec3f size, Material* material) {
	this->pos = pos;
	this->rot = rot;
	this->size = size;
	this->material = material;
}

float Plane::intersect(vec3f rayOrigin, vec3f rayDir) {
	float dot = vec3f::dot(rot, rayDir);
	if (fabsf(dot) <= 0.001f) return -1.0f;
	float dist = (vec3f::dot(pos - rayOrigin, rot) + size.x) / dot;
	return dist > MIN_DEPTH ? dist : -1.f;
}

vec3f Plane::getNormal(vec3f hitPoint) {
	return rot;
}