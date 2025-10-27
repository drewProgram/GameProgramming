#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <variant>
#include <string>
#include <unordered_map>
#include <any>
#include <memory>

#include "Shader.h"
#include "Texture.h"

enum class Type { Mat4, Vec3, Float, Int };

enum class Prop { Vector, Position };

struct UniformValue
{
	Type type;

	// variant is similar to union
	std::variant<glm::mat4, glm::vec3, float, int> value;
};

using UniformMap = std::unordered_map<std::string, UniformValue>;
using TexturesContainer = std::vector<std::shared_ptr<Texture>>;

class Shape
{
public:
	virtual ~Shape() = default;

	virtual void Render(const UniformMap& uniforms) = 0;

	virtual void SetProperty(const Prop prop, const std::any& value) {};

	TexturesContainer textures;
protected:
	std::vector<float> vertexData;
	std::vector<unsigned int> indicesData;

	Shader* shader = nullptr;

	unsigned int VAO = 0, VBO = 0, EBO = 0;
};

