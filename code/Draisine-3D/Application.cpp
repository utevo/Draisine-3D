#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "Camera.h"
#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "TexturesMapper.h"
#include "Renderer.h"
#include "OrtogonalProjection.h"
#include "PerspectiveProjection.h"
#include "PositionFrontUpView.h"
#include "primitives/Trapeze.h"
#include "primitives/Ground.h"
#include "primitives/Cube.h"
#include "composites/railway.h"
#include "composites/Wheels.h"
#include "primitives/Cylinder.h"
using namespace std;
const GLuint WIDTH = 800, HEIGHT = 600;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 prevPos(0.0f, 0.0f, 0.0f);
Camera cam = Camera(cameraPos, cameraFront, cameraUp);;
double fps = 0.0;
const float FPS_CONST = 0.01f * 60.0f;
float step = 0.0f;
double prev_X, prev_Y;
void mouse_callback(GLFWwindow* window, double new_X, double new_Y)
{
	cam.Rotate_Mouse(prev_X - new_X, prev_Y - new_Y);
	glfwSetCursorPos(window, prev_X, prev_Y);
}
//for keys pressed once
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
//for "sticky keys"
void process_sticky_keys(GLFWwindow* window, Cube& skybox)
{
	prevPos = cam.getPos();
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)//FASTER
		step = (FPS_CONST / fps)* 10 ;
	else step = FPS_CONST / fps;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//STEP_FORWARD
		cam.Step_Longtitudal(step);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//STEP_BACK
		cam.Step_Longtitudal(-step);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//STEP_LEFT
		cam.Step_Lateral(-step);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //STEP_RIGHT
		cam.Step_Lateral(step);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) //STEP_UP
		cam.Step_Vertical(step);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) //STEP_DOWN
		cam.Step_Vertical(-step);
	skybox.move(cam.getPos() - prevPos);
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

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");
		std::shared_ptr<PositionFrontUpView> view = std::make_shared<PositionFrontUpView>(cameraPos, cameraFront, cameraUp);
		// std::shared_ptr<OrtogonalProjection> projection = std::make_shared<OrtogonalProjection>(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
		float fov = 45.0f;
		std::shared_ptr<PerspectiveProjection> projection = std::make_shared<PerspectiveProjection>(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.25f, 100.0f);


		auto texture = std::make_shared<Texture>("textures/iipw.png");
		auto texture2 = std::make_shared<Texture>("textures/weiti.png");
		auto groundtex = std::make_shared<Texture>("textures/cracked_ground.png", true);
		auto skybox_tex = std::make_shared<Texture>("textures/skybox.png");
		auto cart_tex = std::make_shared<Texture>("textures/cart.png");
		auto test_tex = std::make_shared<Texture>("textures/test_cyl.png");

		Trapeze trapeze(texture);
		Trapeze trapeze2(texture2, { 1.0, 0.0, -1.0 });
		Ground ground(groundtex);
		Wheels w= Wheels();
		Railway railway(3);
		Cylinder c = Cylinder(test_tex);
		Cube skybox(skybox_tex, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 40.0, 40.0, 40.0 });
		Cube cart(cart_tex, { 1.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 }, { 0.5, 0.02, 1.0 });		//can be any size as long as proportions are kept

		auto shader = std::make_shared<Shader>("shader.vert", "shader.frag");
		
		double lastTime = glfwGetTime(), deltaT = 0.0, spf = 0.0;
		float currentFrame;
		int nbFrames = 0;
		
		// main event loop
		while (!glfwWindowShouldClose(window)) {
			currentFrame = glfwGetTime(); 
			deltaT = currentFrame - lastTime; 
			nbFrames++;
			if (deltaT >= 0.25) {
				fps = 4 * nbFrames;
				nbFrames = 0;
				lastTime += 0.25f;
			}
			cout << "Current Frame: " << currentFrame << "\nFPS: " << fps << endl;
			
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			cameraPos = cam.getPos();
			cameraFront = cam.getFront();
			view->setPosition(cameraPos);
			view->setFront(cameraFront);
			
			glm::mat4 viewMatrix = view->getMatrix();
			shader->setUniformMat4("VIEW", viewMatrix);
			glm::mat4 projectionMatrix = projection->getMatrix();
			shader->setUniformMat4("PROJECTION", projectionMatrix);
			
			//ground.render(shader);
            railway.render(shader);
			cart.render(shader);
			skybox.render(shader);
			w.render(shader);
			//c.render(shader);
			mouse_callback(window, prev_X, prev_Y);


			glfwSwapBuffers(window);
			process_sticky_keys(window, skybox);
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