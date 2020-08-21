#pragma once

#include <random>
#include <stdio.h>
#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/norm.hpp>

// I want to expand on this eventually
class Random
{
public:
	static std::random_device s_Device;
	static std::mt19937 s_Engine;

	template<typename T>
	inline static T GetRandomInRange(T a, T b)
	{
		static_assert(false, 
			std::sprintf("Random does not support this data type: %v", typeid(T).name));
	}

	template<>
	inline static float GetRandomInRange(float a, float b)
	{
		std::uniform_real_distribution<float> distribution(a, b);
		return distribution(s_Engine);
	}

	template<>
	inline static int GetRandomInRange(int a, int b)
	{
		std::uniform_int_distribution<int> distribution(a, b);
		return distribution(s_Engine);
	}

	// for lazy random scatter rendering
	inline static glm::vec3 GetRandomVecInRange(float min, float max) {
		return glm::vec3(GetRandomInRange<float>(min, max), GetRandomInRange<float>(min, max), GetRandomInRange<float>(min, max));
	}

	inline static glm::vec3 GetRandomInUnitSphere() {
		while (true) {
			auto p = Random::GetRandomVecInRange(-1.0f, 1.0f);
			if (glm::length2(p) >= 1) continue;
			return p;
		}
	}

	// for lambertian scatter rendering
	inline static glm::vec3 GetRandomUnitVec() {
		float a = GetRandomInRange<float>(0, 2 * glm::pi<float>());
		float z = GetRandomInRange<float>(-1.0f , 1.0f);
		float r = glm::sqrt(1 - z * z);
		return glm::vec3(r * glm::cos(a), r * glm::sin(a), z);
	}

	// for hemispheric scatter rendering
	inline static glm::vec3 GetRandomInHemisphere(const glm::vec3& normal) {
		glm::vec3 inUnitSphere = GetRandomInUnitSphere();
		if (glm::dot(inUnitSphere, normal) > 0.0f) {
			return inUnitSphere;
		}
		return -inUnitSphere;
	}
};
