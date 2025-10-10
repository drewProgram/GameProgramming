#include "VectorShape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <print>
#include <tuple>
#include <cmath>

VectorShape::VectorShape(Shader* _shader, unsigned int _VAO, unsigned int _VBO)
{
	shader = _shader;
	VAO = _VAO;
	VBO = _VBO;

	mainVector = { 1.0f, 0.0f, 0.0f };
	

	vertexData = {
		// line positions
		0.0f, 0.0f, 0.0f,  // vector start
		0.1f, 0.0f, 0.0f,  // vector end

		// triangle positions
		0.07f,  0.03f,  0.0f,  // left base
		0.07f, -0.03f,  0.0f,  // right base
		0.1f ,  0.0f ,  0.0f   // top
	};

	// first bind vertex array, then bind and set vertex buffer, and then configure vertex attributes
	glBindVertexArray(VAO);

	// binds created object to a target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copy user defined data to the currently bound buffer with target GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	// telling opengl how to interpret the vertex attributes on the vertex data
	/*
		param 1: which vertex attr we want to configure
		param 2: size of the vertex attrb
		param 3: type of data
		param 4: whether data needs to be normalized
		param 5: stride - space between consecutive vertex attr (as each value in this case is a float 3d vector)
		param 6: offset where this attr data begins in the buffer
	*/
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// vertex attributes are off by default, we need to enable them
	glEnableVertexAttribArray(0);

	// after defining the attribute pointers, the vbo is registred as being bound to this vao, so we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VectorShape::Render(const UniformMap& uniforms)
{
	// use the created program and the vertex array
	if (!shader)
	{
		std::println("ERROR: VectorShape SHADER IS NULLPTR!");
		return;
	}

	shader->Use();

	// set uniforms here
	if (auto it = uniforms.find("transform"); it != uniforms.end())
	{
		glm::mat4 transform = std::get<glm::mat4>(it->second.value);

		glm::vec3 baseVector = { 1.0f, 0.0f, 0.0f };

		float angle = acos(glm::dot(glm::normalize(baseVector), glm::normalize(mainVector)));

		float length = glm::length(mainVector);

		transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));

		transform = glm::scale(transform, glm::vec3(length, 1.0f, 1.0f));

		//transform = glm::translate(transform, position);

		shader->SetMat4("transform", transform);
	}

	if (auto it = uniforms.find("color"); it != uniforms.end())
	{
		shader->SetVec3("color", std::get<glm::vec3>(it->second.value));
	}

	// bind vertex array of object you want to render
	glBindVertexArray(VAO);

	// draw line
	glDrawArrays(GL_LINES, 0, 2);

	// draw triangle
	glDrawArrays(GL_TRIANGLES, 2, 3);

	// unbind vertex array of rendered object
	glBindVertexArray(0);
}

void VectorShape::SetProperty(const Prop prop, const std::any& value)
{
	if (prop == Prop::Vector)
	{
		mainVector = std::any_cast<glm::vec3>(value);
		return;
	}
	if (prop == Prop::Position)
	{
		position = std::any_cast<glm::vec3>(value);
		return;
	}
}
