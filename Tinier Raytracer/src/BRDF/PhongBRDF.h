#pragma once
#include "BRDF.h"
#include "..\Renderer\Util\Util.h"

class PhongBRDF : public BRDF {
public:
	void f(std::shared_ptr<BaseObject> object, Vector3 N, std::shared_ptr<Light> light, Vector3 V, Colour& colour) {

		Vector3 colourVec(colour.r, colour.g, colour.b);
		Vector3 L = (light->m_position - V).normalize();
		Vector3 R = Util::reflect(L, N).normalize();
		R = R * -1;
		float weight = dot(N, L) < 0.0f ? (0.0f) : dot(N, L);
		setDiffuse(Vector3(1,1,1) * m_kd * light->m_intensity * weight);

		float dotSpec = dot(R, V.normalize());
		float spec_int = (powf(dotSpec, m_alpha));
		setSpecular(Vector3(1,1,1) * spec_int * m_ks);


	}

	void setParameters(float ks, float kd, float ka, float alpha) {
		m_kd = kd;
		m_ks = ks;
		m_alpha = alpha;
		setAmbient(Vector3(ka, ka, ka));
	}

private:
	float m_ks;
	float m_kd;
	float m_alpha;
};
