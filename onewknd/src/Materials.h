#pragma once
#include "IMaterial.h"
#include "common.h"
#include "Ray.h"

class Lambertian : public IMaterial {
public:
	Lambertian(const color& a)
		: Albedo(a) {}


	virtual bool Scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered)
		const override;

public:
	color Albedo;
};


class Metal : public IMaterial {
public:
	Metal(const color& a)
		: Albedo(a) {}

	virtual bool Scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered)
		const override;

public:
	color Albedo;
private:
	static glm::vec3 reflect(const glm::vec3& in, const glm::vec3& normal);
};