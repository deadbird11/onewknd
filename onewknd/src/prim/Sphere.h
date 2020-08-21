#pragma once
#include "common.h"
#include "IHittable.h"

class IMaterial;

class Sphere : public IHittable {
public:
	Sphere() 
		: Center(glm::vec3(0.0f)), Radius(1.0f) {}
	Sphere(point3 center, float radius, Ref<IMaterial> material)
		: Center(center), Radius(radius), p_Material(material) {}

	virtual bool Hit(const Ray& r,
		float tMin, float tMax, HitRecord& rec) const override;

public:
	point3 Center;
	float Radius;
	Ref<IMaterial> p_Material;
};