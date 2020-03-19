#pragma once
#include <math.h>

class Vector3;
inline float dot(Vector3 v, Vector3 w);

class Vector3 {
public:
	float x;
	float y;
	float z;
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3 operator*(float scalar) { return Vector3(x*scalar, y*scalar, z*scalar); }
	float length() {
		return sqrt(dot(*this, *this));
	}
	Vector3 normalize() { return *this*(1 / sqrt(dot(*this, *this))); }
	Vector3 operator+(Vector3 v) { return Vector3(x + v.x, y + v.y, z + v.z); }
	Vector3 operator-(Vector3 v) { return Vector3(x - v.x, y - v.y, z - v.z); }
	Vector3 mul(Vector3 v) {
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
};

inline float dot(Vector3 v, Vector3 w) { return  v.x * w.x + v.y * w.y + v.z * w.z; }
inline Vector3 cross(Vector3 v, Vector3 w) {
	return Vector3(v.y*w.z - v.z*w.y, v.z*w.x - v.x*w.z,v.x*w.y - v.y*w.x);
}
