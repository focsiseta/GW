#ifndef __MESHLOADER
#define __MESHLOADER
#include <iostream>
#include <vector>
#include <unordered_map>
#include "../components.h"
#include "../../libraries/assimp/assimp/Importer.hpp"
#include "../../libraries/assimp/assimp/scene.h"
#include "../../libraries/assimp/assimp/postprocess.h"



struct Vertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	glm::vec2 TexCoords;

};

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::string id;
	unsigned int VBO, VAO, EBO;

public:
	Mesh(std::vector<Vertex> vertices,
		std::vector<unsigned int> indices);
	void loadInGPU();
	void draw();

};

class Model { 
private:
	std::vector<Mesh> meshes;
	//The reason for <string,type> is because either way we are going to search for textures by name and not by tag
	//so it's faster this way
	std::unordered_map<std::string,aiTextureType>textures;
	std::string id;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	void processTextures(const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

public:
	Model(std::string& path);
	Model(std::string&& path);
	std::vector<Mesh>* getMeshVector() { return &meshes; }
	void Draw(); //TODO Draw code for Model
	void printTexturePaths();
	std::string getDirectory();
	~Model();
};


#endif