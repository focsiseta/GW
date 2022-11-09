#ifndef __CAMERA
#define __CAMERA
#include "../components.h"

class QuatCamera {
public:
	QuatCamera(glm::vec3 position, glm::vec3 up);
	glm::mat4 getViewMatrix();
	glm::mat4 getCameraMatrix();
	glm::mat4 cameraMatrix;
	void cameraControlls(GLFWwindow* window);
private:
	glm::quat Position;
	glm::quat Direction;
	glm::quat Up;
	glm::quat Right;
	void updateCamera();
	void rotateDirection(glm::quat axis, float radians);

};
glm::mat4 projectionMatrix(float near, float far, float aspectRatio);
#endif // !__CAMERA