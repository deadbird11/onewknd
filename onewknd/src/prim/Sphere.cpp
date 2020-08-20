#include "Sphere.h"

bool Sphere::Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
	glm::vec3 oc = r.Orig - Center;
	float a = glm::length2(r.Dir);
	float halfB = glm::dot(oc, r.Dir);
	float c = glm::length2(oc) - Radius * Radius;
	float discriminant = halfB * halfB - a * c;

	if (discriminant > 0) {
		float root = glm::sqrt(discriminant);

		auto setRecord = [&rec, this, &r](float temp) {
			rec.t = temp;
			rec.p = r.at(rec.t);
			glm::vec3 outwardNormal{ (rec.p - Center) / Radius };
			rec.SetFaceNormal(r, outwardNormal);
		};

		float temp = (-halfB - root) / a;
		if (temp < tMax && temp > tMin) {
			setRecord(temp);
			return true;
		}
		
		temp = (-halfB + root) / a;
		if (temp < tMax && temp > tMin) {
			setRecord(temp);
			return true;
		}
	}
	return false;
}