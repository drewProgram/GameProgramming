#include "Entity.h"

#include <glm/gtc/type_ptr.hpp>

Entity::Entity(std::shared_ptr<Shape> s)
	: shape(s)
{
	randomVec = { 0.0f, 0.0f, 0.0f };
	position = { 0.0f, 0.0f, 0.0f };
	color = { 1.0f, 0.0f, 0.0f };
	transform = glm::mat4(1.0f);
}

void Entity::Render()
{
	UniformMap uniforms;

	transform = glm::mat4(1.0f);

	transform = glm::translate(transform, position);

	shape->SetProperty(Prop::Vector, randomVec);
	shape->SetProperty(Prop::Position, position);

	uniforms["transform"] = { Type::Mat4, transform };
	uniforms["color"] = { Type::Vec3, color };

	shape->Render(uniforms);
}

