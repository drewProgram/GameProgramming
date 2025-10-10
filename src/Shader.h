#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <print>

class Shader
{
public:
	/* Path starts at project root folder (where the .sln file is) */
	Shader(const char* vertexPath, const char* fragmentPath);

	unsigned int id;

	// activate shader 
	void Use();

	// utility uniform functions
	// single value
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	// vectors
	void SetVec3(const std::string& name, const glm::vec3& vec) const;

	// matrices
	void SetMat4(const std::string& name, const glm::mat4& mat) const;
};
