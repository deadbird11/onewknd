#pragma once

#include <random>
#include <stdio.h>
#include <typeinfo>
#include <glm/glm.hpp>

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

	inline static glm::vec3 GetRandomVecInRange(float min, float max) {
		return glm::vec3(GetRandomInRange<float>(min, max), GetRandomInRange<float>(min, max), GetRandomInRange<float>(min, max));
	}
};
