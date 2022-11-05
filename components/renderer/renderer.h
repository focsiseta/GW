#ifndef __RENDERER
#define __RENDERER

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../meshloader/meshloader.h"
#include "../shader/shader.h"
#include <iostream>
#include <string>


#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

class Renderer {
 

public:
	std::string log;
	Renderer() : window(NULL) {};
	~Renderer() {
		glfwTerminate();
	};
	GLFWwindow* window;
	GLFWwindow* buildOpenglContext();
	static Model* loadModel(std::string&& path);
	static Model* loadModel(std::string& path);
private:
	static std::unordered_map<std::string, Model> modelTable;






};


#endif
