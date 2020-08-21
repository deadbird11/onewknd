#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <memory>
#include <limits>
#include "util/Random.h"

using color = glm::vec3;
using point3 = glm::vec3;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, class... Args>
constexpr Ref<T> MakeRef(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

const float infinity = std::numeric_limits<float>::infinity();

glm::vec3 randomInUnitSphere();