#define STB_IMAGE_IMPLEMENTATION
#include "components/renderer/renderer.h"
#include "components/camera/camera.h"
#define _USE_MATH_DEFINES
#include <math.h>


void processInput(GLFWwindow* window);


int main() {

	Renderer context{};
	auto window = context.buildOpenglContext();
	if (window == nullptr) return -1;
	glViewport(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);
	containerModel* test = Renderer::loadModelFromPath("./assets/models/backpack/backpack.obj");
	Shader* shader = Renderer::createShader("shaders/simple/vertex.glsl", "shaders/simple/fragment.glsl");
	shader->useProgram();
	glm::mat4 projMatrix = glm::perspective((float)M_PI / 4.0f, 1.0f, 0.01f, 1000.0f);
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0.0f), glm::vec3(0, 1, 0));
	QuatCamera cam{ glm::vec3(0,0,-10),glm::vec3(0, 1, 0) };
	shader->uMat4("uViewMatrix", cam.getViewMatrix(), false);
	shader->uMat4("uProjectionMatrix", projectionMatrix(0.1f,100.f,1.0f), false);
	shader->uMat4("uModel", glm::mat4(1.0f), false);
	glClearColor(0, 1, 0, 1);

    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window);
		test->pModel->Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	
	return 0;

}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}