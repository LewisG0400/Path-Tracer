#include "World.h"

World::World() {
	
}

void World::addRenderObject(RenderObject* obj) {
	renderables.push_back(obj);
}

vec3f World::hemisphereSample(float a, float b) {
	float r = sqrtf(fabsf(1.0f - a - b));
	float phi = 2 * 3.141 * b;
	return vec3f(cosf(phi) * r, sinf(phi) * r, a);
}

vec3f World::refract(vec3f incident, vec3f normal, float ior) {
	float angle = vec3<float>::dot(incident, normal);

	float iorOutside = 1.0f, iorInside = ior;

	//Entering surface
	if(angle < 0.0f) {
		angle = -angle;
	}
	else {
		iorOutside = ior;
		iorInside = 1.0f;
		normal = normal * -1.0f;
	}

	float n = iorOutside / iorInside;

	float sinT = n * n * (1 - angle * angle);
	if(sinT > 1.0f) return vec3f(0.0f, 0.0f, 0.0f);
	float cosT = sqrtf(1.0f - sinT);
	return vec3<float>::normalise(incident * n + normal * (n * angle - cosT));
}

//Needs optimised
RenderObject* World::intersect(vec3f rayOrigin, vec3f rayDir, float& dist) {
	RenderObject* closest = nullptr;

	bool hit = false;
	float minDist = 100000.f;
	for (auto object : renderables) {
		float dist = object->intersect(rayOrigin, rayDir);
		if (dist == -1.f) continue;
		if (hit) {
			if (dist < minDist) {
				minDist = dist;
				closest = object;
			}
		}
		else {
			hit = true;
			minDist = dist;
			closest = object;
		}
	}

	if (!hit) {
		dist = -1.f;
		return nullptr;
	}
	dist = minDist;
	return closest;
}

void World::render(vec3f rayOrigin, vec3f rayDir, int depth, vec3f& colour) {
	if (depth > 5) {
		return;
	}

	float dist = 0.0f;
	RenderObject* closest = intersect(rayOrigin, rayDir, dist);

	if (closest == nullptr) return;

	vec3f hit = rayOrigin + rayDir * dist;
	vec3f norm = closest->getNormal(hit);

	Material* material = closest->getMaterial();

	if (material->type == MaterialType::DIFFUSE) {
		vec3f emmission = vec3f(material->emmisitivity, material->emmisitivity, material->emmisitivity);
		
		vec3f rotX, rotY;
		float a = getRand();
		float b = getRand();
		vec3f sampledDir = hemisphereSample(a, b);
		vec3f dir = vec3<float>::normalise(sampledDir + norm);

		float costheta = fabsf(vec3<float>::dot(dir, norm));

		vec3f temp = vec3f(0.0f, 0.0f, 0.0f);
		render(hit, dir, depth + 1, temp);
		colour = colour + emmission + (material->colour * temp * costheta / PROBABILITY);
	}
	else if(material->type == MaterialType::REFLECTIVE) {
		vec3f dir = vec3<float>::normalise(vec3<float>::reflect(rayDir, norm));

		vec3f temp = vec3f(0.0f, 0.0f, 0.0f);
		render(hit, dir, depth + 1, temp);

		colour = colour + temp;
	}
	else if(material->type == MaterialType::GLASS) {
		float iorOutside = 1.0f, iorInside = material->ior;

		float costheta1 = vec3<float>::dot(rayDir, norm);

		float R0 = (iorOutside - iorInside) / (iorOutside + iorInside);
		R0 = R0 * R0;

		bool outside = false;

		if(costheta1 < 0.0f) {
			iorOutside = iorInside;
			iorInside = 1.0f;

			outside = true;
		}

		float probability = R0 + (1.0f - R0) * powf(1.0f + costheta1, 5.0f);

		vec3f refractionDir = refract(rayDir, norm, material->ior);

		float val = getRand();

		//std::cout << val << ", " << probability << std::endl;

		if((refractionDir != vec3f(0.0f, 0.0f, 0.0f) && val > probability) || !outside) {
			rayDir = refractionDir;
		}
		else {
			rayDir = vec3<float>::normalise(vec3<float>::reflect(rayDir, norm));
		}
		vec3f temp = vec3f(0.0f, 0.0f, 0.0f);
		render(hit, rayDir, depth + 1, temp);
		colour = colour + temp * 1.15;
	}
}

float World::getRand() {
	return (float)rand() / (float) RAND_MAX;
}

World::~World() {
	for (auto x : renderables) delete x;
	renderables.clear();
}