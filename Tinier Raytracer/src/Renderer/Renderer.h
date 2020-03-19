#pragma once
#include "../BRDF/BRDF.h"
#include "Image.h"
#include "Util/Util.h"
#include "Util/Vector3.h"
#include <memory>
#include <vector>

class Renderer {
public:
	Renderer(const IScene &scene) {
		m_scene = scene;
		m_dim = m_scene.getDimensions();
	}

	//Calculate colour following ray
	Colour cast(Vector3& origin, Vector3& direction, float depth) {

		//Only recursively trace until we hit the maximum amount of steps
		if (depth > MAX_DEPTH) {
			return Colour::BLACK;
		}

		Colour finalColour(0,0,0);
		Ray* ray = new Ray(origin, direction);
		std::shared_ptr<BaseObject> closestObj;

		//Find closest object
		float hit = Util::trace(ray, closestObj, m_scene);

		if (!closestObj) {
			return Colour::BLACK;
		}

		//Get BRDF of surface
		std::shared_ptr<BRDF> brdf = closestObj->m_material.getBRDF();
		Vector3 hitPosition = ray->origin + ray->direction * hit;
		Vector3 N = closestObj->normal(hitPosition);
		
		//Flip direction and calculate reflection vector
		direction = direction * -1;
		Vector3 R = Util::reflect(direction, N).normalize();
		Vector3 newOrigin = hitPosition + (N * 0.001);

		//Get colour following reflected ray
		Colour reflectionColour = cast(newOrigin, R, depth + 1);

		//Set diffuse and specular colour
		Vector3 diff(0, 0, 0);
		Vector3 spec(0, 0, 0);

		//For all lights in the scene calculate the diffuse and specular coefficients
		for (auto l : m_scene.getLights()) {

			//Light vector
			Vector3 L = l->m_position - hitPosition;

			//Shadow checking
			Vector3 shadow_orig = dot(N, L) < 0.0 ? hitPosition - (N * 0.0001) : hitPosition + (N * 0.0001);
			Ray* shadowRay = new Ray(shadow_orig, L.normalize());
			std::shared_ptr<BaseObject> interceptObj;

			//Check if there is an object in between surface and light source
			float interceptDistance = Util::trace(shadowRay, interceptObj, m_scene);
			interceptDistance = ((shadow_orig + (shadowRay->direction * interceptDistance)) - shadow_orig).length();
			float lightDistance = L.length();

			if (!interceptObj || (interceptObj && interceptDistance > (lightDistance))) {
				//Not in shadow

				//Calculate diffuse and specular components
				brdf->f(closestObj, N, l, hitPosition, reflectionColour);

				//Add to overall contribution
				diff = diff + brdf->getDiffuse();
				spec = spec + brdf->getSpecular();

			}

			delete shadowRay;
			shadowRay = nullptr;
		}

		delete ray;
		ray = nullptr;

		//Calculate final diffuse and specular colour
		Colour diffColour = Colour(closestObj->m_material.getColour().x * diff.x, closestObj->m_material.getColour().y * diff.y, closestObj->m_material.getColour().z * diff.z);
		Colour specColour = Colour(spec.x, spec.y, spec.z);
		
		//Add everything together and additionally the reflected colour from the scene, scaled by the ambient factor
		finalColour = diffColour + specColour + reflectionColour * brdf->getAmbient();
		
		//Set alpha to 100%
		finalColour.a = 1.0;

		return finalColour;
	}

	void render() {

		Image result(m_dim.width, m_dim.height);
		
		//Loop through each pixel
		for (int row = 0; row < m_dim.height; row++) {
			for (int column = 0; column < m_dim.width; column++) {

				//Origin and direction
				Vector3 org(0.0f, 0.0f, 0.0f);

				//Calculate direction of ray adding 0.5 pixel offset and calculating z from FOV = 2*tan(h/2*z)
				Vector3 dir = (Vector3((float(column) + 0.5) - m_dim.width / 2.f, m_dim.height / 2.f - (float(row) + 0.5), -m_dim.height/(2.f * tan(1.0472 / 2.0f))) - org).normalize();

				//Set colour in image
				Colour resColour = cast(org, dir, 0);
				result.set(column, row, resColour);
				
			}
		}

		//Save image...
		result.save(".\\");
	}

private:
	
	IScene m_scene;
	ImageSize m_dim;

	//Maximum recursove reflections
	const int MAX_DEPTH = 8;
};