#pragma once
#include "Util\Vector3.h"
#include "..\BRDF\BRDF.h"

class Material {
public:
	void setColour(Vector3 colour) {
		m_colour = colour;
	}

	Vector3 getColour() {
		return m_colour;
	}

	void setBRDF(std::shared_ptr<BRDF> brdf) {
		m_brdf = brdf;
	}

	std::shared_ptr<BRDF> getBRDF() {
		return m_brdf;
	}

private:
	Vector3 m_colour;
	std::shared_ptr<BRDF> m_brdf;
};