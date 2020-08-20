#include "HittableList.h"

HittableList::HittableList(Ref<IHittable> obj)
	: objects{ obj } {}

bool HittableList::Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
	HitRecord tempRec;
	bool hitAnything = false;
	auto closestT = tMax;

	for (const auto& object : objects) {
		if (object->Hit(r, tMin, closestT, tempRec)) {
			hitAnything = true;
			closestT = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}