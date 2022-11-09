#ifndef __RENDERER
#define __RENDERER
#include "../components.h"
#include "../meshloader/meshloader.h"
#include "../shader/shader.h"
#include "../texture/texture.h"
#include <iostream>
#include <string>


#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

struct containerModel {
	Model* pModel;
};

class Renderer {
 

public:
	std::string log;
	Renderer() : window(NULL) {};
	~Renderer() {
		for (auto a : modelTable) {
			
			delete a.second.pModel;

		}
		glfwTerminate();
	};
	GLFWwindow* window;
	GLFWwindow* buildOpenglContext();
	static containerModel* loadModelFromPath(std::string&& path);
	static Texture* loadTexture(std::string& path);
	static Shader* createShader(std::string& vertexPath, std::string& fragmentPath, std::string name = std::string{ "shader_" });
	static Shader* createShader(std::string&& vertexPath, std::string&& fragmentPath, std::string name = std::string{ "shader_" });
	static void printTables();
	static std::unordered_map<std::string, containerModel> modelTable;
	static std::unordered_map<std::string, Texture> textureTable;
	static std::unordered_map<std::string, Shader> shaderTable;

private:







};


#endif
