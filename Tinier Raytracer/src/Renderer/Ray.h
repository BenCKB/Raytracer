#pragma once
#include "Util\Vector3.h"

class Ray {
public:
	Vector3 origin;
	Vector3 direction;
	Ray(Vector3 o, Vector3 d) { origin = o, direction = d; }
};