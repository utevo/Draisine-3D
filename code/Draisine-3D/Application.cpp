#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "TexturesMapper.h"

#include "objects/Square.h"

#include "OrtogonalProjection.h"
#include "PositionFrontUpView.h"

using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
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

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		GLCall(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes));
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		GLCall(glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes));
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		//const std::string vertexShaderSource = "shader.vert";
		//const std::string fragmentShaderSource = "shader.frag";
		//Shader shader(vertexShaderSource, fragmentShaderSource);

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

		//GLCall(glEnable(GL_DEPTH_TEST));

		//VertexBuffer vertexBuffer(vertices, sizeof(vertices));

		//VertexBufferLayout vertexBufferLayout;
		//// vertex geometry data
		//vertexBufferLayout.addFloat(3);
		//// vertex color data
		//vertexBufferLayout.addFloat(3);
		//// vertex texture coordinates
		//vertexBufferLayout.addFloat(2);

		//VertexArray vertexArray = VertexArray();
		//vertexArray.link(vertexBuffer, vertexBufferLayout);

		//IndexBuffer indexBuffer(indices, sizeof(indices));
	
		//Texture texture0("textures/weiti.png");
		//Texture texture1("textures/iipw.png");
		//std::vector < pair<std::string, Texture&> > textureMapperMapping = { pair<std::string, Texture&>{"Texture0", texture0 }, pair<std::string, Texture&>{ "Texture1", texture1 }};
		//TexturesMapper texturesMapper(textureMapperMapping, shader);


		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		std::shared_ptr<View> view = std::make_shared<PositionFrontUpView>(cameraPos, cameraFront, cameraUp);
		std::shared_ptr<Projection> projection = std::make_shared<OrtogonalProjection>(1, 1, 1, 1);
		Renderer renderer = Renderer(*view, *projection);
		Square square = Square();

		// main event loop
		while (!glfwWindowShouldClose(window)) {
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			renderer.clear();

			//texturesMapper.bind();
			//render(vertexArray, indexBuffer, shader);
			
			square.render(renderer);
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
