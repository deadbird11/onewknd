#include "common.h"

glm::vec3 reflect(const glm::vec3& in, const glm::vec3& normal) {
	return in - 2 * glm::dot(in, normal) * normal;
}

glm::vec3 refract(const glm::vec3& uv, const glm::vec3& normal, float etaiOverEtat) {
	float cosTheta = glm::dot(-uv, normal);
	glm::vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * normal);
	glm::vec3 rOutParallel = -sqrt(fabs(1.0f - length2(rOutPerp))) * normal;
	return rOutPerp + rOutParallel;
}

float schlick(float cosine, float refIdx) {
	float r0 = (1 - refIdx) / (1 + refIdx);
	r0 *= r0;
	return r0 + (1 - r0) * glm::pow(1 - cosine, 5);
}