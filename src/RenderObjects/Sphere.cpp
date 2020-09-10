#include "Sphere.h"

Sphere::Sphere() {
	pos = vec3f(0.0f, 0.0f, 0.0f);
	rot = vec3f(0.0f, 0.0f, 0.0f);
	size = vec3f(1.0f, 1.0f, 1.0f);
	material = new Material();
}

Sphere::Sphere(vec3f pos) {
	this->pos = pos;
	rot = vec3f(0.0f, 0.0f, 0.0f);
	size = vec3f(1.0f, 1.0f, 1.0f);
	material = new Material();
	material->colour = vec3f(0.1f, 0.2f, 0.7f);
}

Sphere::Sphere(vec3f pos, vec3f rot, vec3f size, Material* material) {
	this->pos = pos;
	this->rot = rot;
	this->size = size;
	this->material = material;
}

float Sphere::intersect(vec3f rayPos, vec3f rayDir) {
	vec3f rayToCentre = rayPos - pos;
	float b = vec3<float>::dot(((rayToCentre) * 2.f), rayDir);
	float c = vec3<float>::dot(rayToCentre, rayToCentre) - powf(size.x, 2);
	float discriminant = powf(b, 2) - 4 * c;
	if (discriminant < 0) return -1.f;
	else discriminant = sqrtf(discriminant);
	float p1 = -b + discriminant;
	float p2 = -b - discriminant;

	return p2 > MIN_DEPTH ? p2 / 2.f : (p1 > MIN_DEPTH ? p1 / 2.f : -1.f);
}


vec3f Sphere::getNormal(vec3f hitPoint) {
	return vec3<float>::normalise(hitPoint - pos);
}

Sphere::~Sphere() {

}