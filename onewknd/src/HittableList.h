#pragma once
#include "IHittable.h"
#include <vector>
#include <memory>

class HittableList : public IHittable {
public:
	HittableList() {}
	HittableList(Ref<IHittable> object);

	inline void Clear() { objects.clear(); }
	inline void Add(Ref<IHittable> object) { objects.push_back(object); }

	virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

private:
	std::vector<Ref<IHittable>> objects;
};


