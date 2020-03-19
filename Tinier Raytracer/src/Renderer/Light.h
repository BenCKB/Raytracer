#pragma once
#include "Image.h"

class Light {
public:
	Light(Vector3 position, float intensity) {
		m_position = position;
		m_intensity = intensity;

	}

	Vector3 m_position;
	float m_intensity;
};