#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "TexturesMapper.h"

#include "objects/Square.h"
#include "objects/Ground.h"
#include "objects/ThreeD_Obj.h"

#include "OrtogonalProjection.h"
#include "PerspectiveProjection.h"
#include "PositionFrontUpView.h"



using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

glm::mat4 rotationMat(1);
glm::mat4 quarterRotation(1);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f,-1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float step = 0.1;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// cout << key << endl;

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)	//STEP_FORWARD
		cameraPos += step*cameraFront;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)//STEP_BACK
		cameraPos -= step*cameraFront;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)//STEP_RIGHT
		cameraPos += step * glm::vec3( quarterRotation * glm::vec4(cameraFront,1.0));
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)//STEP_LEFT
		cameraPos += step * glm::vec3(glm::inverse(quarterRotation) * glm::vec4(cameraFront, 1.0));
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)	//ROTATE_COUNTER_CLOCKWISE
		cameraFront=glm::vec3(rotationMat * glm::vec4(cameraFront, 1.0));
	
	if (key == GLFW_KEY_E && action == GLFW_PRESS)	//ROTATE_CLOCKWISE
		cameraFront = glm::vec3(glm::inverse(rotationMat)*glm::vec4(cameraFront, 1.0));
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void render(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) {
	shader.bind();
	vertexArray.bind();
	indexBuffer.bind();
	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

void clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 04", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		
		glEnable(GL_DEPTH_TEST);

		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");


	
		std::shared_ptr<PositionFrontUpView> view = std::make_shared<PositionFrontUpView>(cameraPos, cameraFront, cameraUp);
		//std::shared_ptr<OrtogonalProjection> projection = std::make_shared<OrtogonalProjection>(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
		float fov = 45.f;
		std::shared_ptr<PerspectiveProjection> projection = std::make_shared<PerspectiveProjection>(glm::radians(fov), (float) WIDTH / (float) HEIGHT , 1.0f, 100.0f);


		Renderer renderer = Renderer(*view, *projection);

		Square square = Square();
		Ground gr = Ground();
		ThreeD_Obj cube = ThreeD_Obj();
		rotationMat = glm::rotate(rotationMat, 0.1f, glm::vec3(0.0, 1.0, 0.0));
		quarterRotation= glm::rotate(rotationMat, -3.14152f/2 , glm::vec3(0.0, 1.0, 0.0));
		//
		// main event loop
		while (!glfwWindowShouldClose(window)) {
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			renderer.clear();


			view->setPosition(cameraPos);
			view->setFront(cameraFront);

			//square.render(renderer);
			gr.render(renderer);
			cube.render(renderer);
			// Swap the screen buffers
			glfwSwapBuffers(window);
		}

	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
