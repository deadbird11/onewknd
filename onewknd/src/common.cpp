#include "common.h"

glm::vec3 randomInUnitSphere() {
	 while (true) {
		 auto p = Random::GetRandomVecInRange(-1.0f, 1.0f);
		 if (glm::length2(p) >= 1) continue;
		 return p;
	 }
}