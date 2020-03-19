#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Renderer\Renderer.h"
#include "Scenes\DemoScene.h"
#include "Scenes\SphereScene.h"

int main(int argc, char* argv[]) {

	//Width and height of output image
	const int WIDTH(1020); //1020 2048
	const int HEIGHT(780); //780 1080

	//Define scene geometry and materials
	//DemoScene scene(WIDTH, HEIGHT);
	SphereScene scene(WIDTH, HEIGHT);

	//Create renderer
	Renderer renderer(scene);
	
	//Render scene, also saves image
	renderer.render();

	return 0;
}