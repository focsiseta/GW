#include "renderer.h"
std::unordered_map<std::string, Model> Renderer::modelTable{};
GLFWwindow* Renderer::buildOpenglContext() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	 window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "WIP", NULL, NULL);
	 if (window == NULL) {
		 log.append("GLFW::UNABLE TO CREATE WINDOW\n");
		 glfwTerminate();
		 return nullptr;
	 }
	 glfwMakeContextCurrent(window);
	 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	 {
		 log.append("Failed to initialize GLAD\n");
		 return nullptr;
	 }
	 return window;
}
Model* Renderer::loadModel(std::string&& path) {
	Renderer::modelTable.insert({ path,Model{path} });
	auto reference = Renderer::modelTable.find(path);
	if (reference == Renderer::modelTable.end()) return nullptr;
	return &(reference->second);
}
Model* Renderer::loadModel(std::string& path) {
	Renderer::modelTable.insert({ path,Model{path} });
	auto reference = Renderer::modelTable.find(path);
	if (reference == Renderer::modelTable.end()) return nullptr;
	return &(reference->second);
}