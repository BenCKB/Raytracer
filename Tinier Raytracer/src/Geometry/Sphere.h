#pragma once
#include "BaseObject.h"

class Sphere : public BaseObject{
public:
	Vector3 center;
	float radius;
	Sphere(Vector3 c, float r) { center = c, radius = r; }
	
	bool intersect(Ray* ray, float&t) {

		Vector3 origToCentre = center - ray->origin;

		float projVec = dot(origToCentre, ray->direction);
		float distanceToCentre2 = dot(origToCentre, origToCentre) - projVec * projVec;
		
		if (distanceToCentre2 > radius* radius) return false;
		float hitToProjCentre = sqrtf(radius * radius - distanceToCentre2);
		
		t = projVec - hitToProjCentre;

		float t1 = projVec + hitToProjCentre;
		
		t = (t < 0) ? t = t1 : t;

		return t < 0 ? false : true;
	}

	Vector3 normal(Vector3 intersection) {
		return (intersection - center).normalize();
	}
};