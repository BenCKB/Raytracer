#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "..\..\vendor\STB\include\stb_image_write.h"

#include "Util/Vector3.h"
#include "Util/Util.h"

class Colour {
public:
	Colour() : r(0), g(0), b(0), a(1.0f) {}
	Colour(Vector3 c) : r(c.x), g(c.y), b(c.z), a(1.0f) {}
	Colour(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1.0f) {}
	Colour(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
	
	Colour operator+(const Colour& c) { return Colour(c.r + r, c.g + g, c.b + b, c.a + a); }
	Colour operator*(const Colour& c) { return Colour(c.r * r, c.g * g, c.b * b, c.a * a); }
	Colour operator*(const float& c) { return Colour(c * r, c * g, c * b, c * a); }

	Vector3 xyz() { return Vector3(r,g,b); }

	void setColour(const Colour& c) {
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}

	void setColour(float _r, float _g, float _b, float _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	float r;
	float g;
	float b;
	float a;

	static const Colour BLACK;
};

class Image {
public:
	Image(int width, int height);
	~Image();
	Colour* at(int x, int y);
	void set(int x, int y, const Colour& c);
	bool save(std::string path);
private:
	std::vector<Colour> m_data;
	int m_width;
	int m_height;
};