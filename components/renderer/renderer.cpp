#include "renderer.h"
std::unordered_map<std::string, containerModel> Renderer::modelTable{};
std::unordered_map<std::string, Texture> Renderer::textureTable{};
std::unordered_map<std::string, Shader> Renderer::shaderTable{};
GLFWwindow* Renderer::buildOpenglContext() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	 window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GW", NULL, NULL);
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
	 glEnable(GL_DEPTH_TEST);
	 return window;
}
//TODO switching to heap allocation from stack allocation for models, they can be quite large 
//or even better, having a struct that referes that that memory and has all the buffers to use it with opengl
// and then allocate that on memory
//do it for shaders too


containerModel* Renderer::loadModelFromPath(std::string&& path) {
	Model* model = new Model{ path };
	Renderer::modelTable.insert({ path,containerModel{model} });
	auto reference = Renderer::modelTable.find(path);
	if (reference == Renderer::modelTable.end()) return nullptr;
	return &(reference->second);
}
Texture* Renderer::loadTexture(std::string& path) {

	Texture a = loadTextureFromPath(path);
	if (a.isOk) {
		Renderer::textureTable.insert({ path,a });
		auto reference = Renderer::textureTable.find(path);
		return &(reference->second);
	}
	return nullptr;
}
Shader* Renderer::createShader(std::string& vertexPath, std::string& fragmentPath, std::string shaderName) {
	//Shader(const char* shader_name, const char* vspath, const char* fspath);
	static long int ShaderIstanceCounter = 0;
	ShaderIstanceCounter++;
	if(shaderName.compare("shader_") == 0) shaderName.append(std::to_string(ShaderIstanceCounter));
	Renderer::shaderTable.insert({ shaderName,Shader{ shaderName.c_str(),vertexPath.c_str(),fragmentPath.c_str()} });

	return &Renderer::shaderTable.find(shaderName)->second;
}
Shader* Renderer::createShader(std::string&& vertexPath, std::string&& fragmentPath, std::string shaderName) {
	//Shader(const char* shader_name, const char* vspath, const char* fspath);
	static long int ShaderIstanceCounter = 0;
	ShaderIstanceCounter++;
	if (shaderName.compare("shader_") == 0) shaderName.append(std::to_string(ShaderIstanceCounter));
	Renderer::shaderTable.insert({
		shaderName,Shader{ shaderName.c_str(),vertexPath.c_str(),fragmentPath.c_str()} 
		});
	auto value = Renderer::shaderTable.find(shaderName);
	
	return &value->second != nullptr ? &value->second : nullptr;
	
}
void Renderer::printTables() {
	
	for (auto a : Renderer::shaderTable) {
		
		a.second.printName();
		std::cout << a.second.test << std::endl;

	}

}