#pragma once

#include <math.h>

template <class T>
class vec3 {
public:
	T x, y, z;

	vec3() : x((T)1), y((T)1), z((T)1) {}
	vec3(T x, T y, T z) : x(x), y(y), z(z) {}


	inline vec3<T> operator +(vec3<T> other) {
		return vec3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
	}


	inline vec3<T> operator -(vec3<T> other) {
		return vec3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
	}


	inline vec3<T> operator*(T amt) {
		return vec3<T>(this->x * amt, this->y * amt, this->z * amt);
	}

	//Component-wise multiplication
	inline vec3<T> operator*(vec3<T> other) {
		return vec3<T>(this->x * other.x, this->y * other.y, this->z * other.z);
	}


	inline vec3<T> operator /(float amt) {
		return vec3<T>(this->x / amt, this->y / amt, this->z / amt);
	}


	inline vec3<T> operator %(vec3<float> b) {
		return vec3<float>(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}


	inline float dot(vec3<T> other) {
		return this->x * other.x + this->y * other.y + this->z * other.z;
	}


	inline static float dot(vec3<T> vec1, vec3<T> vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}


	inline vec3<T> cross(vec3<T> other) {
		//det|i  j  k |
		//	 |x1 y1 z1|
		//	 |x2 y2 z2|
		T newX = this->y * other.z - this->z - other.y;
		T newY = -(this->x * other.z - this->z * other.x);
		T newZ = this->x * other.y - this->y * other.x;

		return vec3<T>(newX, newY, newZ);
	}


	inline float length() {
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}


	inline static float length(vec3<T> vec) {
		return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
	}


	inline vec3<T> normalise() {
		float len = length();
		return vec3<T>(this->x / len, this->y / len, this->z / len);
	}


	inline static vec3<T> normalise(vec3<T> vec) {
		return vec.normalise();
	}


	inline static vec3<T> clamp(vec3<T> vec, T min, T max) {
		vec3<T>ret = vec3<T>(0.0f, 0.0f, 0.0f);
		ret.x = vec.x < min ? min : (vec.x > max ? max : vec.x);
		ret.y = vec.y < min ? min : (vec.y > max ? max : vec.y);
		ret.z = vec.z < min ? min : (vec.z > max ? max : vec.z);
		return ret;
	}


	inline bool operator != (vec3<T> other) {
		if (this->x == other.x && this->y == other.y && this->z == other.z) return true;
		return false;
	}
};

typedef vec3<float> vec3f;