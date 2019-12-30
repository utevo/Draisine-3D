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
#include "Renderer.h"
#include "Texture.h"


using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 04", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		GLCall(glViewport(0, 0, WIDTH, HEIGHT));

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		GLCall(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes));
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		GLCall(glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes));
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		const std::string vertexShaderSource = "shader.vert";
		const std::string fragmentShaderSource = "shader.frag";
		Shader shader(vertexShaderSource, fragmentShaderSource);

		// Set up vertex data 
		GLfloat vertices[] = {
			// coordinates			// color			// texture
			 0.25f,  0.5f,  0.0f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,
			-0.75f,  0.5f,  0.0f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,
			-0.25f, -0.5f,  0.0f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
			 0.75f, -0.5f,  0.0f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,
		};

		VertexBuffer vertexBuffer(vertices, sizeof(vertices));

		VertexBufferLayout vertexBufferLayout;
		// vertex geometry data
		vertexBufferLayout.addFloat(3);
		// vertex color data
		vertexBufferLayout.addFloat(3);
		// vertex texture coordinates
		vertexBufferLayout.addFloat(2);

		VertexArray vertexArray = VertexArray();
		vertexArray.link(vertexBuffer, vertexBufferLayout);

		IndexBuffer indexBuffer(indices, sizeof(indices));
	
		Texture texture("textures/iipw.png");
		Renderer renderer;

		// main event loop
		while (!glfwWindowShouldClose(window)) {
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			renderer.clear();

			texture.bind(0);
			shader.setUniformInt("Texture0", 0);

			renderer.draw(vertexArray, indexBuffer, shader);

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
