#pragma once
#include "common.h"
#include "IHittable.h"

class Sphere : public IHittable {
public:
	Sphere() 
		: Center(glm::vec3(0.0f)), Radius(1.0f) {}
	Sphere(point3 center, float radius)
		: Center(center), Radius(radius) {}

	virtual bool Hit(const Ray& r,
		float tMin, float tMax, HitRecord& rec) const override;

public:
	point3 Center;
	float Radius;
};