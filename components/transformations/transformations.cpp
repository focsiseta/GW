#include "transformations.h"
#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

void rotateVector(glm::vec3& axisToRot, glm::vec3& refAxis, float degree) {

	auto rot = glm::angleAxis(glm::radians(degree), glm::normalize(refAxis));
	axisToRot = rot * axisToRot;


}
Mesh generateFlatPlane(float scale) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	float boundBox[] = { -100.0f, -100.0f,0.0f, 100.0f, 10.0f, 100.0f };
	float texCoords[] =
	{
		0.0f,0.0f,scale,0.0f,scale,scale,0.0f,scale
	};
	float normals[] =
	{
		0.0f,1.0f,0.0f

	};
	float points[] = {
		boundBox[0],boundBox[1] - 0.01f,boundBox[5],
		boundBox[3],boundBox[1],boundBox[5],
		boundBox[3],boundBox[1],boundBox[2],
		boundBox[0],boundBox[1],boundBox[2],
	};
	for (int i = 0; i < 4; i++) {
		Vertex vert{};
		//Missing tangtent and bitangent
		//TODO Algorithm for Tangent and Bitangent
		vert.Position.x = points[i * 3];
		vert.Position.y = points[(i + 1) + 3];
		vert.Position.z = points[(i + 2) + 3];
		vert.Normal.x = normals[0];
		vert.Normal.y = normals[1];
		vert.Normal.z = normals[2];
		vert.TexCoords.x = texCoords[i * 2];
		vert.TexCoords.y = texCoords[i + 2];
		vertices.push_back(vert);
	}

}
Geometry::Geometry() {
	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;
	this->position = glm::vec3(0.0f);
	this->relativeFrame = glm::mat4(1.0);
	this->frame = glm::lookAt(position, Z_AXIS, Y_AXIS);
	this->frame = glm::inverse(this->frame);
	this->resetFrame = this->frame;
	this->rotation = glm::mat4(1.0);
	this->translation = glm::vec3(0.0);
	this->scaling = glm::mat4(1.0);
}

void Geometry::rotX(float degrees) {
	pitch += glm::radians(degrees);
	update();
}
void Geometry::rotY(float degrees) {
	yaw += glm::radians(degrees);
	update();
}
void Geometry::rotZ(float degrees) {
	roll += glm::radians(degrees);
	update();
}
glm::mat4 Geometry::getFrame() {

	return frame;

}
void Geometry::update() {
	this->frame *= scaling;
	this->frame = glm::translate(this->frame,this->translation);
	this->frame = glm::rotate(this->frame, pitch, X_AXIS);
	this->frame = glm::rotate(this->frame, yaw, Y_AXIS);
	this->frame = glm::rotate(this->frame, roll, Z_AXIS);
	this->frame = this->relativeFrame * this->frame;
	this->scaling = glm::mat4(1.0);
	this->translation = glm::vec3(0.0);
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->roll = 0.0f;

	
}