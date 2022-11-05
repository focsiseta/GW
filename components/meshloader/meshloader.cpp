#include "meshloader.h"

//Thanks to learnopengl for making things a little bit cleaner

/*
	Ecco come funziona in generale il codice per caricare il modello da file

	Con il costruttore di model si apre il file e poi si chiama processNode

	processNode non fa altro che aprire le aiMesh prese da aiScene usando processMesh
	e le carica nel vettore di mesh presente nell'oggetto

	processMesh scompatta i dati iterando per il numero di vertici presenti nella mesh, 
	ogni vertice e' composto dalla posizione,normale,tangente,bitangente e coordinata UV

	per "scompattare i dati" viene inteso che si porta dal formato di aiMesh a quello di glm,
	perche' noi andremmo a lavorare con quello (per quanto ne so glm::vec* ci garantisce mem
	contigua, se si riuscisse direttamente a lavorare con aiMesh sarebbe estremamente piu' comodo
	eviterebbe parecchio codice boilerplate)

	Una volta scompattati i vari dati dei vertici della mesh, si passa agli indici, 
	gli indici sono suddivisi in facce e le facce non sono altro che le primitive 
	con cui stiamo lavorando, in questo caso stiamo parlando di triangoli 
	perche' aiProcess_Triangulate sara' sempre attivo ed ogni cosa verra' triangolarizzata
*/
//TODO scrivere il codice per caricare le mesh in GPU e usare la classe renderer come factory per i model
Model::Model(std::string& path) {
	Assimp::Importer importer;
	std::string placeHolder = path;
	const aiScene* scene = importer.ReadFile(placeHolder, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace);
	//Path for placeholder object
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		//This should never fail
		placeHolder = "./assets/models/backpack/backpack.obj";
		scene = importer.ReadFile(placeHolder, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace);
		//Log code here
	}
	auto index = placeHolder.find_last_of('/');
	//+1 because I want directories to end with '/'
	directory = placeHolder.substr(0, index + 1);
	aiNode* rootNode = scene->mRootNode;
	//This gives us all the data we need to render the model itself
	processNode(rootNode, scene);
	auto tmp = scene->mMaterials[1]->GetTextureCount(aiTextureType_DIFFUSE);
	aiString texPath;
	scene->mMaterials[1]->GetTexture(aiTextureType_DIFFUSE, 0, &texPath);
	//std::cout << texPath.C_Str() << "\n" << tmp << std::endl;


}
Model::Model(std::string&& path) {
	Assimp::Importer importer;
	std::string placeHolder = path;
	const aiScene* scene = importer.ReadFile(placeHolder, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace);
	 //Path for placeholder object
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		//This should never fail
		placeHolder = "./assets/models/backpack/backpack.obj";
		scene = importer.ReadFile(placeHolder, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace);
		//Log code here
	}
	auto index = placeHolder.find_last_of('/');
	//+1 because I want directories to end with '/'
	directory = placeHolder.substr(0, index+1);
	aiNode* rootNode = scene->mRootNode;
	//This gives us all the data we need to render the model itself
	processNode(rootNode, scene);
	auto tmp = scene->mMaterials[1]->GetTextureCount(aiTextureType_DIFFUSE);
	aiString texPath;
	scene->mMaterials[1]->GetTexture(aiTextureType_DIFFUSE, 0, &texPath);
	//std::cout << texPath.C_Str() << "\n" << tmp << std::endl;

}

void Model::processNode(aiNode* node, const aiScene* scene) {

	if (node == nullptr || scene == nullptr) {
		return;
	}
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}

}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices{};
	std::vector<unsigned int> indices{};
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 vertex;
		Vertex v;
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;
		v.Position = vertex;
		if (mesh->HasNormals()) {
			vertex.x = mesh->mNormals[i].x;
			vertex.y = mesh->mNormals[i].y;
			vertex.z = mesh->mNormals[i].z;
			v.Normal = vertex;
		}
		vertex.x = mesh->mTangents[i].x;
		vertex.y = mesh->mTangents[i].y;
		vertex.z = mesh->mTangents[i].z;
		v.Tangent = vertex;
		vertex.x = mesh->mBitangents[i].x;
		vertex.y = mesh->mBitangents[i].y;
		vertex.z = mesh->mBitangents[i].z;
		v.Bitangent = vertex;
		if (mesh->HasTextureCoords(0)) {
			vertex.x = mesh->mTextureCoords[0][i].x;
			vertex.y = mesh->mTextureCoords[0][i].y;
			v.TexCoords = glm::vec2(vertex.x, vertex.y);
		}
		else {
			v.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(v);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[i]);
		}
		
	}
	return Mesh{vertices,indices};
	
}

std::string Model::getDirectory() {
	return directory;
}

Mesh::Mesh(std::vector<Vertex> vertices,
	std::vector<unsigned int> indices) {
	
	this->vertices = vertices;
	this->indices = indices;
	this->id = std::string("TODO"); //TODO

}