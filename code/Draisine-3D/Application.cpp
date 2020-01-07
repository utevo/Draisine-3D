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
//TODO:make camera_movement and rotation class
#define GLOBAL_REVERSE_SENSITIVITY 5000
#define UPPER_BOUND 89.0f*glm::half_pi<float>()/90.0f
#define LOWER_BOUND -89.0f*glm::half_pi<float>()/90.0f
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

double prev_X, prev_Y;
double _yaw, _pitch;
bool first_mouse_call = true;


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f,-1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float step = 0.005f;//TODO: step should account for fps



int X_sensitivity = 20; //range 1-100
int Y_sensitivity = 20; //range 1-100
void mouse_callback(GLFWwindow* window, double new_X, double new_Y)
{
	if (first_mouse_call)
	{
		prev_X = new_X;
		prev_Y = new_Y;
		_yaw = 0.0f;
		_pitch = 0.0f;
		first_mouse_call = false;
		return;
	}

	glfwSetCursorPos(window, prev_X, prev_Y);

	glm::mat4 rotationMat(1);

	float X_offset = prev_X - new_X;
	float Y_offset = prev_Y - new_Y; 
	

	X_offset *= X_sensitivity;
	Y_offset *= Y_sensitivity;

	X_offset /= GLOBAL_REVERSE_SENSITIVITY;
	Y_offset /= GLOBAL_REVERSE_SENSITIVITY;
	
	_yaw += (X_offset / glm::half_pi<float>());
	_pitch += (Y_offset / glm::half_pi<float>());

	if (_pitch > UPPER_BOUND)_pitch = UPPER_BOUND;
	if (_pitch < LOWER_BOUND)_pitch = LOWER_BOUND;
	prev_X = new_X;
	prev_Y = new_Y;

	rotationMat = glm::rotate(rotationMat, float(_yaw), glm::vec3(0.0, 1.0, 0.0));
	rotationMat = glm::rotate(rotationMat, float(_pitch), glm::vec3(1.0, 0.0, 0.0));
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraFront = glm::vec3(rotationMat * glm::vec4(cameraFront, 1.0));
	cameraUp = glm::vec3(rotationMat * glm::vec4(cameraUp, 1.0));

}
//for keys pressed once
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// cout << key << endl;

		
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
//for "sticky keys"
void process_sticky_keys(GLFWwindow* window)
{
//TODO: step should account for fps
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//STEP_FORWARD
		cameraPos += step * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//STEP_BACK
		cameraPos -= step * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {//STEP_LEFT
		glm::mat4 quarterRotation(1);
		quarterRotation = glm::rotate(quarterRotation, -glm::half_pi<float>(), cameraUp);
		glm::vec3 lateral_vector(quarterRotation * glm::vec4(cameraFront, 1.0));
		lateral_vector[1]=0.0f;
		cameraPos -= step * lateral_vector;
	}
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {//STEP_LEFT
		glm::mat4 quarterRotation(1);
		quarterRotation = glm::rotate(quarterRotation, -glm::half_pi<float>(), cameraUp);
		glm::vec3 lateral_vector(quarterRotation * glm::vec4(cameraFront, 1.0));
		lateral_vector[1] = 0.0f;
		cameraPos += step * lateral_vector;
	}
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
		
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetKeyCallback(window, key_callback);
	
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(window, &prev_X, &prev_Y);

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
		

		

		//
		// main event loop
		while (!glfwWindowShouldClose(window)) {
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			

			renderer.clear();


			view->setPosition(cameraPos);
			view->setFront(cameraFront);

			//square.render(renderer);
			gr.render(renderer);

			cube.render(renderer);
			
			mouse_callback(window, prev_X, prev_Y);

			// Swap the screen buffers
			glfwSwapBuffers(window);
			process_sticky_keys(window);
			glfwPollEvents();
		}

	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
