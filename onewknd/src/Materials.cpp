#include "Materials.h"
#include "util/Random.h"

bool Lambertian::Scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
	glm::vec3 scatterDir = rec.Normal + Random::GetRandomUnitVec();
	scattered = Ray(rec.P, scatterDir);
	attenuation = Albedo;
	return true;
}

bool Metal::Scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
	glm::vec3 reflected = reflect(glm::normalize(in.Dir), rec.Normal);
	scattered = Ray(rec.P, reflected);
	attenuation = Albedo;
	return (glm::dot(scattered.Dir, rec.Normal) > 0.0f);
}

bool Dialectric::Scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
	attenuation = color(1.0f);
	float etaiOverEtat = rec.FrontFace ? (1.0f / RefIdx) : RefIdx;	

	glm::vec3 unitDir = glm::normalize(in.Dir);
	float cosTheta = glm::min(glm::dot(-unitDir, rec.Normal), 1.0f);
	float sinTheta = glm::sqrt(1.0f - cosTheta * cosTheta);
	if (etaiOverEtat * sinTheta > 1.0f) {
		glm::vec3 reflected = reflect(unitDir, rec.Normal);
		scattered = Ray(rec.P, reflected);
		return true;
	}
	
	float reflectProb = schlick(cosTheta, etaiOverEtat);
	if (Random::GetRandomInRange<float>(0.0f, 1.0f) < reflectProb) {
		glm::vec3 reflected = reflect(unitDir, rec.Normal);
		scattered = Ray(rec.P, reflected);
		return true;
	}

	glm::vec3 refracted = refract(unitDir, rec.Normal, etaiOverEtat);
	scattered = Ray(rec.P, refracted);
	return true;
}

