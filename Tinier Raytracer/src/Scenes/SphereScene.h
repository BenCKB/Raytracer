#pragma once
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "IScene.h"
#include "..\Renderer\Light.h"
#include "..\Geometry\Sphere.h"
#include "..\Geometry\Plane.h"
#include "..\BRDF\PhongBRDF.h"
#include "..\BRDF\LambertBRDF.h"
#include "..\BRDF\NormalBRDF.h"
#include "..\BRDF\BlinnPhongBRDF.h"
#include "..\BRDF\UnrealEngineBRDF.h"

class SphereScene : public IScene {
public:

	SphereScene(int width, int height) {

		m_width = width;
		m_height = height;

		std::srand(static_cast<unsigned int>(std::time(0)));
		for (int i = 0; i < 100; ++i) {
			
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float m = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float f = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			std::shared_ptr<UnrealEngineBRDF> brdf = std::make_shared<UnrealEngineBRDF>();
			brdf->setParameters(r, m, f);

			float x = -15 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/30);
			float y = -15 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/30);
			float z = -30 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/10);
			float rad = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);

			float c_r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float c_g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float c_b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3(x, y, z), rad);
			sphere->m_material.setColour(Vector3(c_r, c_g, c_b));
			sphere->m_material.setBRDF(brdf);
			brdf->setAlbedo(sphere->m_material.getColour());

			m_object.push_back(sphere);
		}
		std::shared_ptr<LambertBRDF> brdfPlane = std::make_shared<LambertBRDF>();
		std::shared_ptr<Plane> plane = std::make_shared<Plane>(Vector3(0,0,-32), Vector3(0,0,1));
		plane->m_material.setBRDF(brdfPlane);
		plane->m_material.setColour(Vector3(0.3, 0.1, 0.1));
		m_object.push_back(plane);

		m_lights.push_back(std::make_shared<Light>(Vector3(-20.0f, 20.0f, 20.0f), 1.5f));
		m_lights.push_back(std::make_shared<Light>(Vector3(30.f, 50.f, -25.f), 1.8f));
		m_lights.push_back(std::make_shared<Light>(Vector3(30, 20, 30.f), 1.7f));
	}
};