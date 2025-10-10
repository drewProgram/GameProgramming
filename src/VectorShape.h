#pragma once

#include "Shape.h"

#include <vector>

class VectorShape : public Shape
{
public:
	VectorShape(Shader* _shader, unsigned int _VAO, unsigned int _VBO);

	virtual void Render(const UniformMap& uniforms) override;

	virtual void SetProperty(const Prop prop, const std::any& value) override;

private:
	glm::vec3 mainVector;
	glm::vec3 position;
};

