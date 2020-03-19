#pragma once
#include "BRDF.h"
#include "..\Renderer\Util\Util.h"

class UnrealEngineBRDF : public BRDF {
public:
	void f(std::shared_ptr<BaseObject> object, Vector3 N, std::shared_ptr<Light> light, Vector3 V, Colour& colour) {
		
		Vector3 colourVec(colour.r, colour.g, colour.b);
		Vector3 L = (light->m_position - V).normalize();
		Vector3 H = (V.normalize() * -1 + L).normalize();
		V = V * -1;
		float weight = dot(N, L) < 0.0f ? (0.0f) : dot(N, L);
		//setDiffuse(Vector3(1, 1, 1) * light->m_intensity * weight);

		Vector3 D(1.0f, 1.0f, 1.0f);
		Vector3 F(1.0f, 1.0f, 1.0f);
		Vector3 F0(m_f0, m_f0, m_f0);
		Vector3 G(1.0f, 1.0f, 1.0f);

		D = D * D_GGX(N, H, m_roughness * m_roughness);
		F0 = mix(F0, m_albedo.xyz(), m_metalness);
		Vector3 Fschlick = F_Schlick(V, H, F0);
		F = Vector3(F.x * Fschlick.x, F.y * Fschlick.y, F.z * Fschlick.z);
		G = G *  G_SchlickGGX(m_roughness * m_roughness, N, L, V);
		
		Vector3 kd = Vector3(1.0, 1.0, 1.0);//(Vector3(1.0f, 1.0f, 1.0f) - F) * (1.0 - m_metalness);
		Vector3 spec = max((D.mul(F).mul(G)), 0.000001) * (1 /  max((4 * dot(N, V) * dot(N, L)), 0.000001));
		//Vector3 spec = D;
		setDiffuse(kd * (1.0 / 3.1415) * light->m_intensity * weight);
		
		setSpecular(spec * light->m_intensity * weight);

	}

	void setParameters(float roughness, float metlaness, float f0) {
		m_roughness = roughness;
		m_metalness = metlaness;
		m_f0 = f0;
		setAmbient(Vector3(metlaness, metlaness, metlaness));
	}

	void setAlbedo(Colour c) {
		m_albedo = c;
	}

private:
	float m_roughness;
	float m_metalness;
	float m_f0;
	Colour m_albedo;

	float D_GGX(Vector3 N, Vector3 H, float r) {
		float rsqr = r * r;

		float NdotHsqr = dot(N, H) * dot(N, H);

		float c = (NdotHsqr * (rsqr - 1) + 1);

		return (rsqr / (3.1415 * c * c));
	}

	Vector3 F_Schlick(Vector3 V, Vector3 H, Vector3 F0) {

		float VdotH = dot(V, H);

		float ex = pow((1.0 - VdotH), 5.0);

		return F0 + (Vector3(1.0f, 1.0f, 1.0f) - F0) * ex;
	}

	float G1_SchlickGGX(Vector3 N, Vector3 v, float k) {

		float NdotV = dot(N, v);

		float denom = NdotV * (1 - k) + k;

		return NdotV / denom;
	}

	float G_SchlickGGX(float R, Vector3 N, Vector3 L, Vector3 V) {

		float k = pow((R + 1), 2.0) / 8;

		float G1 = G1_SchlickGGX(N, L, k);

		float G2 = G1_SchlickGGX(N, V, k);

		return G1 * G2;
	}

	Vector3 mix(Vector3 x, Vector3 y, float a) {
		return x * (1 - a) + y * a;
	}

	float max(float v, float m) {
		return v < m ? m : v;
	}

	Vector3 max(Vector3 v, float m) {
		Vector3 res;
		res.x = max(res.x, m);
		res.y = max(res.y, m);
		res.z = max(res.z, m);
		return res;
	}

};
