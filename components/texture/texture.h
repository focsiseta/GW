#ifndef __TEXTURE
#define __TEXTURE
#include "../components.h"


struct Texture {
	std::string fullPath;
	std::string name;
	std::string directory;
	bool isOk;
	unsigned int ID;
};

Texture loadTextureFromPath(std::string& path);
Texture loadTextureFromPath(std::string& path, std::string& directory, std::string& name);


#endif // !__TEXTURE

