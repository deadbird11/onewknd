#pragma once
#include "common.h"
#include "Ray.h"
#include "IMaterial.h"

class IMaterial;

struct HitRecord {
	point3 P;
	glm::vec3 Normal;
	Ref<IMaterial> p_Material;
	float T;
	bool FrontFace;

	inline void SetFaceNormal(const Ray& r, const glm::vec3 outwardNormal) {
		FrontFace = glm::dot(r.Dir, outwardNormal) < 0;
		Normal = FrontFace ? outwardNormal : -outwardNormal;
	}
};

class IHittable {
public:
	virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};