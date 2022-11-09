#ifndef __GEOMETRY
#define __GEOMETRY
#include "../components.h"
#include "../meshloader/meshloader.h"

Mesh generateFlatPlane(float scale);
void rotateVector(glm::vec3&, glm::vec3&, float degree);
class Geometry {
public:
	float pitch;
	float yaw;
	float roll;
	Geometry();
	//Isn't the use of lookAt faster ? A view matrix is simply an inverted frame, sooo I mean I could just use that
	glm::mat4 getFrame();
	void rotX(float degrees);
	void rotY(float degress);
	void rotZ(float degrees);
	void update();
private:
	glm::mat4 resetFrame;
	glm::vec3 position;
	glm::vec3 translation;
	glm::mat4 relativeFrame;
	glm::mat4 rotation;
	glm::mat4 scaling;
	glm::mat4 frame;

	

};
#endif
