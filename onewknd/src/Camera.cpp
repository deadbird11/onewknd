#include "Camera.h"

Camera::Camera(
	point3 lookFrom, point3 lookAt, glm::vec3 vup,
	float vfov, float aspectRatio
) {

	float theta = glm::radians(vfov);
	float h = glm::tan(theta / 2.0f);
	const float VIEWPORT_HEIGHT = 2.0f * h;
	const float VIEWPORT_WIDTH = aspectRatio * VIEWPORT_HEIGHT;

	auto w = glm::normalize(lookFrom - lookAt);
	auto u = glm::normalize(glm::cross(vup, w));
	auto v = glm::cross(w, u);

	m_Origin = lookFrom;
	m_Horizontal = VIEWPORT_WIDTH * u;
	m_Vertical = VIEWPORT_HEIGHT * v;
	static const float ONE_HALF = 1.0f / 2.0f;
	m_LowerLeftCorner = m_Origin - m_Horizontal * ONE_HALF - m_Vertical * ONE_HALF - w;
}