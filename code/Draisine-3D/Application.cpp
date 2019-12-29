#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Utilities.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

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



		// Build, compile and link shader program
		std::ifstream vertexShaderFile("shader.vert");
		std::stringstream vertexShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		std::string vertexShaderString = vertexShaderStream.str();
		const GLchar* vertexShaderSource = vertexShaderString.c_str();

		std::ifstream fragmentShaderFile("shader.frag");
		std::stringstream fragmentShaderStream;
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		std::string fragmentShaderString = fragmentShaderStream.str();
		const GLchar* fragmentShaderSource = fragmentShaderString.c_str();

		// Build and compile our shader program
		// Vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLCall(glShaderSource(vertexShader, 1, &vertexShaderSource, NULL));
		GLCall(glCompileShader(vertexShader));
		// Check for compile time errors
		GLint success;
		GLchar infoLog[512];
		GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
		if (!success)
		{
			GLCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
			string msg = string("Vertex shader compilation: ") + infoLog;
			throw exception(msg.c_str());
		}

		// Fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		GLCall(glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL));
		GLCall(glCompileShader(fragmentShader));
		// Check for compile time errors
		GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
		if (!success)
		{
			GLCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
			string msg = string("Fragment shader compilation: ") + infoLog;
			throw exception(msg.c_str());
		}


		// Link shaders
		GLuint shaderProgram = glCreateProgram();
		GLCall(glAttachShader(shaderProgram, vertexShader));
		GLCall(glAttachShader(shaderProgram, fragmentShader));
		GLCall(glLinkProgram(shaderProgram));
		// Check for linking errors
		GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
		if (!success) {
			GLCall(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
			string msg = string("Shader linking: ") + infoLog;
			throw exception(msg.c_str());
		}

		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));


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

		GLuint VAO;
		GLCall(glGenVertexArrays(1, &VAO));
		GLCall(glBindVertexArray(VAO));

		
		VertexBuffer vertexBuffer(vertices, sizeof(vertices));

		// vertex geometry data
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0));
		GLCall(glEnableVertexAttribArray(0));

		// vertex color data
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))));
		GLCall(glEnableVertexAttribArray(1));

		// vertex texture coordinates
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))));
		GLCall(glEnableVertexAttribArray(2));


		IndexBuffer indexBuffer(indices, sizeof(indices));
		

		// Set the texture wrapping parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		// Set texture filtering parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		// prepare textures
		int width, height;
		unsigned char* image = SOIL_load_image("textures/iipw.png", &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
			throw exception("Failed to load texture file");

		GLuint texture0;
		GLCall(glGenTextures(1, &texture0));

		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture0));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		// freeing unnecessary texture stuff
		SOIL_free_image_data(image);
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			// Bind Textures using texture units
			GLCall(glActiveTexture(GL_TEXTURE0));
			GLCall(glBindTexture(GL_TEXTURE_2D, texture0));
			GLCall(glUniform1i(glGetUniformLocation(shaderProgram, "Texture0"), 0));

			// Draw our first triangle
			GLCall(glUseProgram(shaderProgram));

			GLCall(glBindVertexArray(VAO));
			GLCall(glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0));
			GLCall(glBindVertexArray(0));

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		GLCall(glDeleteVertexArrays(1, &VAO));
		// GLCall(glDeleteBuffers(1, &EBO));
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
