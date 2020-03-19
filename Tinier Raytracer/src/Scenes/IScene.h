#pragma once
#include <vector>

#include "..\Geometry\BaseObject.h"
#include "..\Renderer\Light.h"

struct ImageSize {
	int width;
	int height;
};

class IScene {
public:
	ImageSize getDimensions() {
		ImageSize dim;
		dim.width = m_width;
		dim.height = m_height;
		return dim;
	}

	std::vector<std::shared_ptr<BaseObject> > getObjects() { return m_object; }

	std::vector<std::shared_ptr<Light> > getLights() { return m_lights; }

protected:
	std::vector<std::shared_ptr<BaseObject> > m_object;
	std::vector<std::shared_ptr<Light> > m_lights;
	int m_width = 0;
	int m_height = 0;
};