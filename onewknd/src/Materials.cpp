#include "Materials.h"
#include "util/Random.h"

bool Lambertian::Scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
	glm::vec3 scatterDir = rec.Normal + Random::GetRandomUnitVec();
	scattered = Ray(rec.P, scatterDir);
	attenuation = Albedo;
	return true;
}

glm::vec3 Metal::reflect(const glm::vec3& in, const glm::vec3& normal) {
	return in - 2 * glm::dot(in, normal) * normal;
}

bool Metal::Scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
	glm::vec3 reflected = reflect(glm::normalize(in.Dir), rec.Normal);
	scattered = Ray(rec.P, reflected);
	attenuation = Albedo;
	return (glm::dot(scattered.Dir, rec.Normal) > 0.0f);
}

