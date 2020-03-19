#pragma once
#include "BRDF.h"

class LambertBRDF : public BRDF {
public:
	void f(std::shared_ptr<BaseObject> object, Vector3 N, std::shared_ptr<Light> light, Vector3 V, Colour& colour) {
		Vector3 L = (light->m_position - V).normalize();
		float lambert_factor = 1.0f / PI;
		
		Colour diff_Colour = object->m_material.getColour();
		Vector3 factor(diff_Colour.r * lambert_factor, diff_Colour.g * lambert_factor, diff_Colour.b * lambert_factor);
		float NdotL = dot(N, L);
		//return factor * NdotL;
		
		setDiffuse(Vector3(1,1,1) * NdotL);
		setSpecular(Vector3(0, 0, 0));
		setAmbient(Vector3(0, 0, 0));
	}
private:
	float PI = 3.1415f;
};