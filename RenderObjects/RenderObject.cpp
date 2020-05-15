#include "RenderObject.h"

RenderObject::RenderObject() : pos(vec3f(0.0f, 0.0f, 0.0f)), rot(vec3f(0.0f, 0.0f, 0.0f)), size(vec3f(1.0f, 1.0f, 1.0f)), material(new Material()) {}
RenderObject::RenderObject(vec3f pos) : pos(pos), rot(vec3f(0.0f, 0.0f, 0.0f)), size(vec3f(1.0f, 1.0f, 1.0f)), material(new Material()) {}
RenderObject::RenderObject(vec3f pos, vec3f rot, vec3f size, Material* material) : pos(pos), rot(rot), size(size), material(material) {}

MaterialType RenderObject::getType() {
	return material->type;
}

Material* RenderObject::getMaterial() {
	return material;
}

RenderObject::~RenderObject() {

}