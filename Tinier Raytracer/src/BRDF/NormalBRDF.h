#pragma once
#include "BRDF.h"

class NormalBRDF : public BRDF {
public:
	void f(std::shared_ptr<BaseObject> object, Vector3 N, std::shared_ptr<Light> light, Vector3 V, Colour& colour) {
		Vector3 L = (light->m_position - V).normalize();
		Vector3 factor(abs(N.x), abs(N.y), abs(N.z));
		
		setDiffuse(factor); //  * dot(N,L)
		setSpecular(Vector3(0, 0, 0));
	}
};