#ifndef __SHADER
#define __SHADER
#include <glad.h>
#include <string>
#include <string.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#define DEBUG 1
#define START_DEBUG if(DEBUG){
#define END_DEBUG }
static int shaderCounter = 0;
class Shader {
private:

	char shader_name[64];

	char logVS[2048];
	char logFS[2048];
	std::string uniformLog;

	unsigned int vertexShader;
	unsigned int fragmentShader;
	std::vector<std::string> uniforms;
	std::unordered_map<std::string, GLint> uniformMap;
	std::vector<std::string> parseShader(std::string& vertex);
public:
	unsigned int program;
	Shader(const char* shader_name, const char* vspath, const char* fspath);
	// 0 = vertex 1 = fragment
	void printLog(int which);
	void useProgram();
	void uMat4(std::string& uniformName, glm::mat4& data, bool transpose);
	void uMat4(std::string& uniformName, glm::mat4&& data, bool transpose);
	void uMat4(std::string&& uniformName, glm::mat4& data, bool transpose);
	void uMat4(std::string&& uniformName, glm::mat4&& data, bool transpose);
	void uInt(std::string&& uniformName, int data);
	void uFloat(std::string&& uniformName, float data);
	~Shader();

};
std::string readFromFile(const char* path);

#endif