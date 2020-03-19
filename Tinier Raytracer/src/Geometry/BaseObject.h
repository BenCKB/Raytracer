#pragma once
#include "..\Renderer\Ray.h"
#include "..\Renderer\Material.h"

class BaseObject {
public:
	virtual bool intersect(Ray* ray, float& t) = 0;
	virtual Vector3 normal(Vector3 intersection) = 0;
	Material m_material;
};
