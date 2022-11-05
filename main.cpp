#include "components/renderer/renderer.h"
#include "components/meshloader/meshloader.h"
int main() {

	Renderer context{};
	auto window = context.buildOpenglContext();
	if (window == nullptr) return -1;
	glViewport(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);
	Model * test = Renderer::loadModel("./assets/models/backpack/backpack.obj");
	std::cout << "AAA " << test->getDirectory() << std::endl;
	
	return 0;

}