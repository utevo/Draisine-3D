#pragma once

#include "../ImplementedObject.h"


class Square : public ImplementedObject {
public:
	Square() {
		auto vertexBufferAndVertexBufferLayout = initVertexBufferAndVertexBufferLayout();
		_vertexBuffer = vertexBufferAndVertexBufferLayout.first;
		_vertexBufferLayout = vertexBufferAndVertexBufferLayout.second;

		_vertexArray = std::make_shared<VertexArray>();
		_vertexArray->link(*_vertexBuffer, *_vertexBufferLayout);

		_indexBuffer = initIndexBuffer();
		_shader = initShader();
		_texturesMapper = initTexturesMapper();
	}

	virtual ~Square() { }

protected:
	std::pair<std::shared_ptr<VertexBuffer>, std::shared_ptr<VertexBufferLayout> > initVertexBufferAndVertexBufferLayout() override {
		// Set up vertex data 
		GLfloat vertices[] = {
			// coordinates			// color			// texture
			 0.25f,  0.5f,  0.0f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,
			-0.75f,  0.5f,  0.0f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,
			-0.25f, -0.5f,  0.0f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
			 0.75f, -0.5f,  0.0f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

		std::shared_ptr<VertexBufferLayout> vertexBufferLayout = std::make_shared<VertexBufferLayout>();
		//// vertex geometry data
		vertexBufferLayout->addFloat(3);
		//// vertex color data
		vertexBufferLayout->addFloat(3);
		//// vertex texture coordinates
		vertexBufferLayout->addFloat(2);

		std::pair<std::shared_ptr<VertexBuffer>, std::shared_ptr<VertexBufferLayout> > result = { vertexBuffer, vertexBufferLayout };
		return result;
	}

	std::shared_ptr <IndexBuffer> initIndexBuffer() override {
		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,
		};

		std::shared_ptr <IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices));
		return indexBuffer;
	};

	std::shared_ptr <Shader> initShader() override {
		const std::string vertexShaderSource = "shader.vert";
		const std::string fragmentShaderSource = "shader.frag";
		std::shared_ptr <Shader> shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource);

		return shader;
	};

	std::shared_ptr <TexturesMapper> initTexturesMapper() override {
		std::shared_ptr<Texture> texture0 = std::make_shared<Texture>("textures/weiti.png");
		std::shared_ptr<Texture> texture1 = std::make_shared<Texture>("textures/iipw.png");

		std::vector <std::pair<std::string, std::shared_ptr<Texture> > > textureMapperMapping = {
			std::pair<std::string, std::shared_ptr<Texture> > {"Texture0", texture0 },
			std::pair<std::string, std::shared_ptr<Texture> > { "Texture1", texture1 }
		};
		std::shared_ptr<TexturesMapper> texturesMapper = std::make_shared<TexturesMapper>(textureMapperMapping, *_shader);

		return texturesMapper;
	};



};

