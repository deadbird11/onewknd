#pragma once
#include "common.h"

class Ray {
public:

	Ray() = default;

	Ray(const point3& origin, const glm::vec3 dir)
		: Orig(origin), Dir(dir)
	{}

	point3 At(float t) const {
		return Orig + t * Dir;
	}

public:
	point3 Orig;
	glm::vec3 Dir;
};