#include "Camera.h"

Camera::Camera() {
	m_Origin = point3(0.0f);
	m_Horizontal = glm::vec3(VIEWPORT_WIDTH, 0.0f, 0.0f);
	m_Vertical = glm::vec3(0.0f, VIEWPORT_HEIGHT, 0.0f);
	static const float ONE_HALF = 1.0f / 2.0f;
	m_LowerLeftCorner = m_Origin - m_Horizontal * ONE_HALF - m_Vertical * ONE_HALF - glm::vec3(0.0f, 0.0f, FOCAL_LENGTH);
}