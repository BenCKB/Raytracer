#pragma once
#include <memory>
#include "..\Renderer\Util\Vector3.h"
class BaseObject;
class Light;
class Colour;

class BRDF {
public:
	virtual void f(std::shared_ptr<BaseObject> object, Vector3 N, std::shared_ptr<Light> light, Vector3 V, Colour& colour) = 0;
	
	void setDiffuse(Vector3 diff) {
		m_diffuse = diff;
	}
	void setSpecular(Vector3 spec) {
		m_specular = spec;
	}
	void setAmbient(Vector3 amb) {
		m_ambient = amb;
	}

	Vector3 getDiffuse() {
		return m_diffuse;
	}
	Vector3 getSpecular() {
		return m_specular;
	}
	Vector3 getAmbient() {
		return m_ambient;
	}

protected:
	Vector3 m_diffuse;
	Vector3 m_specular;
	Vector3 m_ambient;
};