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
			rec.T = temp;
			rec.P = r.At(rec.T);
			glm::vec3 outwardNormal{ (rec.P - Center) / Radius };
			rec.SetFaceNormal(r, outwardNormal);
			rec.p_Material = p_Material;
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