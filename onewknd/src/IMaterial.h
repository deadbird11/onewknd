#pragma once
#include "Ray.h"
#include "IHittable.h"
#include "common.h"

struct HitRecord;

class IMaterial {
public:
	virtual bool Scatter(const Ray& r, const HitRecord& rec, color& attenuation, Ray& scattered) const = 0;
};