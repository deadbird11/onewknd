#pragma once
#include "common.h"
#include "Ray.h"

struct HitRecord {
	point3 p;
	glm::vec3 normal;
	float t;
	bool frontFace;

	inline void SetFaceNormal(const Ray& r, const glm::vec3 outwardNormal) {
		frontFace = glm::dot(r.Dir, outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class IHittable {
public:
	virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};