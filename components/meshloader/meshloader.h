#ifndef __MESHLOADER
#define __MESHLOADER
#include <iostream>
#include <vector>
#include "../../libraries/assimp/assimp/Importer.hpp"
#include "../../libraries/assimp/assimp/scene.h"
#include "../../libraries/assimp/assimp/postprocess.h"
#include "../../libraries/glad/include/glad/glm/glm.hpp"


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

public:
	Mesh(std::vector<Vertex> vertices,
		std::vector<unsigned int> indices);

};
//TODO
class Model { //This class should inherit from my geometry class
private:
	std::vector<Mesh> meshes;
	std::string id;
	std::string directory;
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

public:
	Model(std::string& path);
	Model(std::string&& path);
	std::string getDirectory();
};


#endif