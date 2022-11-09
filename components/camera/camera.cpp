#include "camera.h"
QuatCamera::QuatCamera(glm::vec3 position, glm::vec3 up) {
	auto nUp = glm::normalize(up);
	this->Position = glm::quat{ 0, position };
	this->Up = glm::quat{ 0,nUp };
	//se siamo posizionati in 0,0,-1 e guardiamo in 0,0,0 la direzione e' 0,0,-1
	glm::vec3 direction = glm::normalize(position - glm::vec3{ 0,0,0 });
	std::cout << direction.x << direction.y << direction.z << std::endl;
	this->Direction = glm::quat{ 0,direction };
	this->Right = glm::quat(0, glm::cross(direction, nUp));
	this->cameraMatrix = glm::mat4(1.0);
}

glm::mat4 QuatCamera::getViewMatrix() {
	auto right = glm::vec3(Right.x, Right.y, Right.z);
	auto up = glm::vec3(Up.x, Up.y, Up.z);
	auto direction = glm::normalize(glm::vec3(Direction.x, Direction.y, Direction.z));
	auto position = glm::vec3(Position.x, Position.y, Position.z);

	//Minus direction it's because when it gets inverted inside lookat we obtain what we want
	auto tmp = glm::lookAt(position, -direction + position, up);

	return tmp;
}
glm::mat4 QuatCamera::getCameraMatrix() {
	auto matrix = this->getViewMatrix(); //builds a new camera matrix each time
	this->cameraMatrix = glm::inverse(matrix);
	return this->cameraMatrix;

}

void QuatCamera::updateCamera() {
	auto up = glm::vec3(0, 1, 0);
	auto direction = glm::normalize(glm::vec3(Direction.x, Direction.y, Direction.z));
	this->Direction = glm::quat(0, direction);
	this->Right = glm::quat(0, glm::normalize(glm::cross(direction, up)));
	//this->Up = glm::quat(0, glm::normalize(glm::cross(direction, -this->Right)));



}
void QuatCamera::rotateDirection(glm::quat axis, float radians) {
	if (axis.w != 0) {
		std::cout << "the axis to rotate around is a rotation instead\n";
	}
	auto tmp = glm::normalize(axis);
	auto rotationQuat = glm::angleAxis(glm::radians(radians), glm::vec3{ tmp.x,tmp.y,tmp.z });
	this->Direction = glm::normalize(rotationQuat * this->Direction * glm::conjugate(rotationQuat));

}