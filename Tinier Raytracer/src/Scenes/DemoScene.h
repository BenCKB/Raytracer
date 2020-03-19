#pragma once
#include <vector>
#include <memory>

#include "..\Renderer\Light.h"
#include "..\Geometry\Sphere.h"
#include "IScene.h"
#include "tiny_obj_loader.h"
#include "..\Geometry\Triangle.h"
#include "..\BRDF\PhongBRDF.h"
#include "..\BRDF\LambertBRDF.h"
#include "..\BRDF\NormalBRDF.h"
#include "..\BRDF\BlinnPhongBrdf.h"
#include "..\BRDF\UnrealEngineBRDF.h"

class DemoScene : public IScene{
public:
	
	DemoScene(int width, int height) {

		m_width = width;
		m_height = height;

		//std::shared_ptr<LambertBRDF> brdf2 = std::make_shared<LambertBRDF>();
		//brdf2->setParameters(0.1, 0.9, 0.0, 10.0f);

	/*	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3(-3.0f, 0.0f, -16.f), 2.0f);
		sphere1->m_material.setColour(Vector3(1.0, 0.0f, 0.0f));
		sphere1->m_material.setBRDF(brdf2);
		std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3(7.f, 5.f, -18.f), 4.0f);
		sphere2->m_material.setColour(Vector3(0.0f, 1.0f, 0.0f));
		sphere2->m_material.setBRDF(brdf2);
		std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector3(width / 1.2f, height / 3.0f, -8.0f), 40.0f);
		sphere3->m_material.setColour(Vector3(0.0f, 0.0f, 1.0f));
		sphere3->m_material.setBRDF(brdf2);*/

		//m_object.push_back(sphere1);
		//m_object.push_back(sphere2);
		//m_object.push_back(sphere3);

		/*m_lights.push_back(std::make_shared<Light>(Vector3(0.0f, 100.0f, 0.0f), 1.0f));
		m_lights.push_back(std::make_shared<Light>(Vector3(0.0f, -100.0f, 0.0f), 1.0f));
		m_lights.push_back(std::make_shared<Light>(Vector3(0.0f, 0.0f, -200.0f), 1.0f));
		m_lights.push_back(std::make_shared<Light>(Vector3(0.0f, 0.0f, 200.0f), 1.0f));
		m_lights.push_back(std::make_shared<Light>(Vector3(-100.0f, 0.0f, 0.0f), 1.0f));
		m_lights.push_back(std::make_shared<Light>(Vector3(100.0f, 0.0f, 0.0f), 1.0f));*/

		//OBJ Loading

		std::string filePath = ".\\res\\models\\box.obj";
		std::string materialPath = ".\\res\\models\\";
		std::string loader_warning;
		std::string loader_error;

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> geometry;
		std::vector<tinyobj::material_t> materials;

		//Read obj data
		bool loader_result = tinyobj::LoadObj(&attrib, &geometry, &materials, &loader_warning, &loader_error, filePath.c_str(), materialPath.c_str());
	
		//Check for warnings and errors
		if (!loader_warning.empty()) {
			std::cout << loader_warning << std::endl;
		}
		
		if (!loader_error.empty()) {
			std::cerr << loader_error << std::endl;
		}

		if (loader_result) {
			for (size_t s = 0; s < geometry.size(); s++) {
				// Loop over faces(polygon)
				size_t index_offset = 0;
				for (size_t f = 0; f < geometry[s].mesh.num_face_vertices.size(); f++) {
					int fv = geometry[s].mesh.num_face_vertices[f];
					std::vector<Vector3> triVerts;
					Vector3 f_normal;
					// Loop over vertices in the face.
					for (size_t v = 0; v < fv; v++) {
						// access to vertex
						tinyobj::index_t idx = geometry[s].mesh.indices[index_offset + v];
						tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
						tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
						tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
						tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
						tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
						tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
						//tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
						//tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];


						triVerts.push_back(Vector3(vx, vy-1, vz - 2.2));
						//triVerts.push_back(Vector3(vx, vy, vz));
						f_normal = Vector3(nx, ny, nz).normalize();
					}

					std::shared_ptr<Triangle> tri1 = std::make_shared<Triangle>(triVerts[0], triVerts[1], triVerts[2]);
					tri1->setNormal(f_normal);
					
					tinyobj::material_t f_material = materials[geometry[s].mesh.material_ids[f]];
					tri1->m_material.setColour(Vector3(f_material.diffuse[0], f_material.diffuse[1], f_material.diffuse[2]));
					std::shared_ptr<BlinnPhongBRDF> brdf = std::make_shared<BlinnPhongBRDF>();
					//brdf->setParameters(1.0, 0.1, 0.05);
					//brdf->setAlbedo(tri1->m_material.getColour());

					brdf->setParameters(0.1, 1.0f, 0.1, 5.0f);
					tri1->m_material.setBRDF(brdf);
					m_object.push_back(tri1);
					index_offset += fv;

				}
			}
		}
		m_lights.push_back(std::make_shared<Light>(Vector3(0.0f, 0.96f, -2.2f), 1.0f));
	}
};