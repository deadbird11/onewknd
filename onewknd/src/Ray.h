#pragma once

#include "common.h"

class Ray {
public:
	Ray(const point3& origin, const glm::vec3 dir)
		: Orig(origin), Dir(dir)
	{}

	point3 at(float t) const {
		return Orig + t * Dir;
	}

public:
	point3 Orig;
	glm::vec3 Dir;
};