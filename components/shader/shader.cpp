#include "shader.h"


void Shader::uMat4(std::string& uniformName, glm::mat4& data, bool transpose) {
	auto t = transpose ? GL_TRUE : GL_FALSE;
	auto location = this->uniformMap.find(uniformName);
	glUniformMatrix4fv((location->second), 1, t, &data[0][0]);
}
void Shader::uMat4(std::string& uniformName, glm::mat4&& data, bool transpose) {
	auto t = transpose ? GL_TRUE : GL_FALSE;
	auto location = this->uniformMap.find(uniformName);
	glUniformMatrix4fv((location->second), 1, t, &data[0][0]);
}
void Shader::uMat4(std::string&& uniformName, glm::mat4& data, bool transpose) {
	auto t = transpose ? GL_TRUE : GL_FALSE;
	auto location = this->uniformMap.find(uniformName);
	glUniformMatrix4fv((location->second), 1, t, &data[0][0]);
}
void Shader::uMat4(std::string&& uniformName, glm::mat4&& data, bool transpose) {
	auto t = transpose ? GL_TRUE : GL_FALSE;
	auto location = this->uniformMap.find(uniformName);
	glUniformMatrix4fv((location->second), 1, t, &data[0][0]);

}
void Shader::uInt(std::string&& uniformName, int data) {
	auto location = this->uniformMap.find(uniformName);
	glUniform1i((location->second), data);

}
void Shader::uFloat(std::string&& uniformName, float data) {
	auto location = this->uniformMap.find(uniformName);
	glUniform1f((location->second), data);

}
Shader::~Shader() {
	std::cout << "shader " << this->shader_name << " is being destroyed\n";
}

Shader::Shader(const char* name, const char* vsPath, const char* fsPath) {
	for (int i = 0; i < 2048; i++) {
		this->logFS[i] = '\0';
		this->logVS[i] = '\0';
		if (i < 64)
			this->shader_name[i] = '\0';
	}
	if (name == NULL) {
		char default_name[64]{ '\0' };
		sprintf_s(default_name, "shader_%d", shaderCounter);
		std::memcpy(this->shader_name, default_name, sizeof(default_name));
	}


	auto sourceVS = readFromFile(vsPath);
	const char* ts = sourceVS.c_str();
	/*
	std::string tmp = readFromFile(vsPath);
	this->sourceVS = tmp.c_str();
	*/
	shaderCounter++;
	int success;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &ts, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {

		glGetShaderInfoLog(vertexShader, 2048, NULL, logVS);
		std::cout << shader_name << "Error compiling vertex shader" << std::endl;

	}
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	auto sourceFS = readFromFile(fsPath);
	const char* st = sourceFS.c_str();

	glShaderSource(fragmentShader, 1, &st, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {

		glGetShaderInfoLog(fragmentShader, 2048, NULL, logFS);
		std::cout << shader_name << "Error compiling fragment shader" << std::endl;

	}
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	auto VertexUniforms = this->parseShader(sourceVS);
	auto FragmentUniforms = this->parseShader(sourceFS);
	for (auto a : FragmentUniforms) {
		VertexUniforms.push_back(a);
	}
	this->uniforms = VertexUniforms;
	START_DEBUG
		for (auto a : this->uniforms) {
			std::cout << "DEBUG UNIFORM LIST:" << a << std::endl;
		}
	END_DEBUG
		for (auto uniformName : this->uniforms) {
			auto location = glGetUniformLocation(this->program, uniformName.c_str());
			if (location == -1) {
				this->uniformLog.append(uniformName);
				this->uniformLog.append(" OpenGL can't find this uniform in shader.\n");
				continue;
			}
			this->uniformMap.insert({ uniformName,location });
		}

}
//This parser doesn't account for struct that can appear in shader, I'll need a more sofisticated one
std::vector<std::string> Shader::parseShader(std::string& vertex) {
	std::vector<std::string> buffer{};
	size_t cursor = 0;
	while ((cursor = vertex.find("uniform ", cursor)) != std::string::npos) {
		//If before keyword uniform there is a '/' it can only be a comment so it's better to avoid
		if (vertex[cursor - 1] == '/') {
			cursor++; //Otherwise we will always parse from the same position
			continue;
		}
		auto semicolon = vertex.find(";", cursor);
		semicolon = semicolon - cursor + 1;
		//substr doesn't go from index to index, instead the first arg is the starting index and the second is
		// how many characters we want to go ahead from index
		//std::cout << vertex.substr(cursor,semicolon) << std::endl;
		std::string tmp = vertex.substr(cursor, semicolon); // uniform type name;
		auto helper = tmp.find_last_of(' ', semicolon - 1);
		semicolon = tmp.find_first_of(';', helper);
		if (semicolon == std::string::npos)
			std::cout << "No semicolon has been found at the end of uniform statement" << std::endl;
		std::string yetAnotherString = tmp.substr(helper + 1, semicolon - helper - 1);
		buffer.push_back(yetAnotherString);
		//std::cout << "Uniform :" << vertex.substr(cursor, semicolon) << std::endl;
		cursor++;

	}
	//std::cout << cursor << " " << std::string::npos << std::endl;
	return buffer;

}
void Shader::printLog(int which) {

	switch (which)
	{
	case 0: {
		std::cout << this->logVS << std::endl;
		break;
	}
	case 1: {
		std::cout << this->logFS << std::endl;
	}
	case 2: {
		std::cout << this->uniformLog << std::endl;
	}
	default: break;
	}

}
void Shader::useProgram() {
	glUseProgram(this->program);

}

std::string readFromFile(const char* path) {
	std::string code;
	std::ifstream shader;
	shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream sStream;
	try {
		shader.open(path);
		sStream << shader.rdbuf();
		code = sStream.str();
		//shader.close();
		//std::stringstream().swap(sStream);
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}
	shader.close();

	//std::cout << code;
	return code;

}

