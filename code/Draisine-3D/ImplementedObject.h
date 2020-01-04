#pragma once

#include "Utilities.h"
#include "Object.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "TexturesMapper.h"
#include "Model.h"


class ImplementedObject : public Object {
public:
	ImplementedObject() 
		: _vertexArray(initVertexArray()), _indexBuffer(initIndexBuffer()), _shader(initShader()), _texturesMapper(initTexturesMapper()) {
	};
	~ImplementedObject() {};

	void render(Renderer& renderer) override {
		_vertexArray.bind();
		_indexBuffer.bind();
		_shader.bind();
		_texturesMapper.bind();

		glm::mat4 modelMatrix = _model.getMatrix();
		glm::mat4 viewMatrix = renderer.getView().getMatrix();
		glm::mat4 projectionMatrix = renderer.getProjection().getMatrix();

		glm::mat4 MVP = modelMatrix * viewMatrix * projectionMatrix;
		_shader.setUniformMat4("MVP", MVP);
		
		GLCall(glDrawElements(GL_TRIANGLES, _indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
	};

	Model& getModel() { return _model; }
	void setModel(const Model& model) { _model = model; }

protected:
	Model _model;

	virtual VertexArray initVertexArray() = 0;
	virtual IndexBuffer initIndexBuffer() = 0;
	virtual Shader initShader() = 0;
	virtual TexturesMapper initTexturesMapper() = 0;

private:
	VertexArray _vertexArray;
	IndexBuffer _indexBuffer;
	Shader _shader;
	TexturesMapper _texturesMapper;


};

