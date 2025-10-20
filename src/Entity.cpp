#include "Entity.h"

#include <glm/gtc/type_ptr.hpp>

Entity::Entity(std::shared_ptr<Shape> s)
	: shape(s)
{
	randomVec = { 0.0f, 0.0f, 0.0f };
	position = { 0.0f, 0.0f, 0.0f };
	rotationAngle = 0.0f;
	colorVec = { 1.0f, 0.0f, 0.0f };
	color = ImVec4(colorVec.x, colorVec.y, colorVec.z, 1.00f);
	transform = glm::mat4(1.0f);
}

void Entity::Render()
{
	UniformMap uniforms;

	transform = glm::mat4(1.0f);

	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	shape->SetProperty(Prop::Vector, randomVec);
	shape->SetProperty(Prop::Position, position);

	uniforms["transform"] = { Type::Mat4, transform };
	uniforms["color"] = { Type::Vec3, colorVec };

	shape->Render(uniforms);
}

