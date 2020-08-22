#pragma once
#include "common.h"
#include "Ray.h"

class Camera {
public:
	Camera(
		point3 lookFrom, point3 lookAt, glm::vec3 vup,
		float vfov, float aspectRatio
	);

	inline Ray GetRay(float s, float t) {
		return Ray(m_Origin, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin);
	}

private:
	point3 m_Origin;
	point3 m_LowerLeftCorner;
	glm::vec3 m_Horizontal;
	glm::vec3 m_Vertical;
};