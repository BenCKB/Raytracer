#pragma once
#include "..\Ray.h"
#include "..\..\Scenes\IScene.h"
#include "..\..\Geometry\BaseObject.h"

class Util {
public:
	inline static float clamp(float val) {
		val = (val > 1.0) ? 1.0 : (val < 0) ? 0 : val;
		return val;
	}

	static inline float trace(Ray* ray, std::shared_ptr<BaseObject>& closestB, IScene& scene) {
		float hit = 0.0;
		float closest = -1;

		for (auto b : scene.getObjects()) {

			if (b->intersect(ray, hit) && (closest > hit || closest <= 0) ) {
				closest = hit;
				closestB = b;
			}
		}

		return closest;
	}

	static inline Vector3 reflect(Vector3& V, Vector3& N) {
		return N * 2.f * (dot(V, N)) - V;
	}

};