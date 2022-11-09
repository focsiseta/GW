#ifndef __ENTITY
#define __ENTITY
#include "../components.h"
#include "../transformations/transformations.h"
class Entity : public Geometry {
public:
	Entity();
private:
	Model* model;
};


#endif
