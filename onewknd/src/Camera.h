#pragma once
#include "common.h"
#include "Ray.h"

static const float ASPECT_RATIO = 16.0f / 9.0f;
static const float VIEWPORT_HEIGHT = 2.0f;
static const float VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
static const float FOCAL_LENGTH = 1.0f;

class Camera {
public:
	Camera();

	inline Ray GetRay(float u, float v) {
		return Ray(m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin);
	}

private:
	point3 m_Origin;
	point3 m_LowerLeftCorner;
	glm::vec3 m_Horizontal;
	glm::vec3 m_Vertical;
};