#pragma once

#include "Shader.h"
#include "Shape.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

class Entity
{
public:
	Entity(std::shared_ptr<Shape> s);

	std::shared_ptr<Shape> shape;

	glm::mat4 transform;

	glm::vec3 position;
	float rotationAngle;

	glm::vec3 colorVec;
	ImVec4 color;

	glm::vec3 randomVec;

	void Render();
};