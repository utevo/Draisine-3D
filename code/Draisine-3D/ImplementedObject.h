#pragma once

#include <iostream>

#include "Utilities.h"
#include "Object.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "TexturesMapper.h"
#include "Model.h"


class ImplementedObject : public Object {
public:
	void init() {
		auto vertexBufferAndVertexBufferLayout = initVertexBufferAndVertexBufferLayout();
		_vertexBuffer = vertexBufferAndVertexBufferLayout.first;
		_vertexBufferLayout = vertexBufferAndVertexBufferLayout.second;

		_vertexArray = std::make_shared<VertexArray>();
		_vertexArray->link(*_vertexBuffer, *_vertexBufferLayout);

		_indexBuffer = initIndexBuffer();
		_shader = initShader();
		_texturesMapper = initTexturesMapper();
	}

	virtual ~ImplementedObject() {};

	void render(Renderer& renderer) override {
		_vertexArray->bind();
		_indexBuffer->bind();
		_shader->bind();
		_texturesMapper->bind();

		glm::mat4 modelMatrix = _model.getMatrix();
		glm::mat4 viewMatrix = renderer.getView().getMatrix();
		glm::mat4 projectionMatrix = renderer.getProjection().getMatrix();

		glm::mat4 MVP =  projectionMatrix * viewMatrix * modelMatrix;

		_shader->setUniformMat4("MVP", MVP);
		
		GLCall(glDrawElements(GL_TRIANGLES, _indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr));
	};

	Model& getModel() { return _model; }
	void setModel(const Model& model) { _model = model; }

protected:
	Model _model;

	std::shared_ptr<VertexBuffer> _vertexBuffer;
	std::shared_ptr<VertexBufferLayout> _vertexBufferLayout;
	std::shared_ptr<VertexArray> _vertexArray;
	std::shared_ptr<IndexBuffer> _indexBuffer;
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<TexturesMapper> _texturesMapper;

	virtual std::pair<std::shared_ptr <VertexBuffer>, std::shared_ptr <VertexBufferLayout>> initVertexBufferAndVertexBufferLayout() {
		std::pair<std::shared_ptr <VertexBuffer>, std::shared_ptr <VertexBufferLayout>> result = { nullptr, nullptr };
		return result;
	}
	virtual std::shared_ptr <IndexBuffer> initIndexBuffer() { return nullptr; }
	virtual std::shared_ptr <Shader> initShader() { return nullptr; }
	virtual std::shared_ptr <TexturesMapper> initTexturesMapper() { return nullptr; }


};

