#define GLM_ENABLE_EXPERIMENTAL

#include "SquareShape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <print>
#include <tuple>
#include <cmath>

SquareShape::SquareShape(Shader* _shader, unsigned int _VAO, unsigned int _VBO, unsigned int _EBO)
{
	shader = _shader;
	VAO = _VAO;
	VBO = _VBO;
	EBO = _EBO;

	position = { 0.0f, 0.0f, 0.0f };
	boundingBox = { 0.0f, 0.0f, 0.0f };

	vertexData = {
		// square positions    // tex coords
		0.0f, 0.0f, 0.0f,      0.0f, 0.0f,  // left base
		0.0f, 1.0f, 0.0f,      0.0f, 1.0f,  // left top
		1.0f, 0.0f, 0.0f,      1.0f, 0.0f,  // right base
		1.0f, 1.0f, 0.0f,      1.0f, 1.0f   // right top
	};

	// triangles indices
	indicesData = {
		0, 1, 3,  // left triangle
		0, 2, 3   // right triangle
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesData.size() * sizeof(unsigned int), indicesData.data(), GL_STATIC_DRAW);

	// stride is defined considering the first position the attrib appears on the array
	// position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture attrib
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SquareShape::Render(const UniformMap& uniforms)
{
	// use the created program and the vertex array
	if (!shader)
	{
		std::println("ERROR: SquareShape SHADER IS NULLPTR!");
		return;
	}

	if (texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->id);
	}

	shader->Use();

	// set uniforms here
	if (auto it = uniforms.find("transform"); it != uniforms.end())
	{
		glm::mat4 transform = std::get<glm::mat4>(it->second.value);

		glm::vec3 baseVector = { 1.0f, 1.0f, 0.0f };

		float angle = atan2(boundingBox.y, boundingBox.x);

		float length = glm::length(boundingBox);

		transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));

		transform = glm::scale(transform, glm::vec3(length, length, 1.0f));

		shader->SetMat4("transform", transform);
	}

	if (auto it = uniforms.find("color"); it != uniforms.end())
	{
		shader->SetVec3("color", std::get<glm::vec3>(it->second.value));
	}

	/*if (auto it = uniforms.find("tex"); it != uniforms.end())
	{
		shader->SetVec3("color", std::get<glm::vec3>(it->second.value));
	}*/
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void SquareShape::SetProperty(const Prop prop, const std::any& value)
{
	if (prop == Prop::Vector)
	{
		boundingBox = std::any_cast<glm::vec3>(value);
		return;
	}

	if (prop == Prop::Position)
	{
		position = std::any_cast<glm::vec3>(value);
		return;
	}
}

