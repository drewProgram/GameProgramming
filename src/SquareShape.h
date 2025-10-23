#pragma once

#include "Shape.h"

class SquareShape : public Shape
{
public:
	SquareShape(Shader* _shader, unsigned int _VAO, unsigned int _VBO, unsigned int _EBO);

	virtual void Render(const UniformMap& uniforms) override;

	virtual void SetProperty(const Prop prop, const std::any& value) override;

private:
	glm::vec3 position;
	glm::vec3 boundingBox;
};