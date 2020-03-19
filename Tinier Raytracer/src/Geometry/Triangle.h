#pragma once
#include "BaseObject.h"
#include "..\Renderer\Util\Vector3.h"
class Triangle : public BaseObject {
public:
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3) : m_v1(v1), m_v2(v2), m_v3(v3) {
		Vector3 edge1 = (m_v2 - m_v1).normalize();
		Vector3 edge2 = (m_v3 - m_v1).normalize();

		m_normal = cross(edge1, edge2).normalize();
	}

	/* [Fast, Minimum Storage Ray/Triangle Intersection] Möller & Trumbore 1997 */
	bool intersect(Ray* ray, float& t) {

		Vector3 edge1 = m_v2 - m_v1;
		Vector3 edge2 = m_v3 - m_v1;

		Vector3 pvec = cross(ray->direction, edge2);
		float det = dot(edge1, pvec);
		
		if (det > -EPSILON && det < EPSILON) {
			return false;
		}

		float inv_det = 1.0f / det;
		Vector3 tvec = ray->origin - m_v1;

		float u = inv_det * dot(tvec, pvec);

		if (u < 0.0 || u > 1.0) {
			return false;
		}

		Vector3 qvec = cross(tvec, edge1);
		float v = inv_det * dot(ray->direction, qvec);

		if (v < 0.0 || u+v > 1.0) {
			return false;
		}

		float distance = inv_det * dot(edge2, qvec);

		if (distance > EPSILON) {
			t = distance;
			return true;
		}

		return false;
	}

	Vector3 normal(Vector3 intersection) {
		return m_normal;
	}

	void setNormal(Vector3 norm) {
		m_normal = norm;
	}

private:
	Vector3 m_v1;
	Vector3 m_v2;
	Vector3 m_v3;
	Vector3 m_normal;
	float EPSILON = 0.000001f;
};