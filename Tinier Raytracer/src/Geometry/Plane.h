#pragma once
#include "BaseObject.h"

class Plane : public BaseObject {
public:

	Vector3 m_origin;
	Vector3 m_normal;

	Plane(Vector3 origin, Vector3 normal) {
		m_origin = origin;
		m_normal = normal;
	}

	bool intersect(Ray* ray, float& t) {
		float RdotN = dot(ray->direction, m_normal);
		if (abs(RdotN) > 0.0000001f) {
			Vector3 l = m_origin - ray->origin;
			t = dot(l, m_normal) / RdotN;
			return t >= 0;
		}
		return false;
	}

	Vector3 normal(Vector3 intersection) {
		return m_normal;
	}
};