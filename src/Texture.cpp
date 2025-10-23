#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <print>

Texture::Texture(const char* pathToTexture)
	: id(0), width(0), height(0), nrChannels(0)
{
	unsigned char* data = stbi_load(pathToTexture, &width, &height, &nrChannels, 0);

	if (data)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		// textures
		// tex coords are defined by(s, t, r) = (x, y, z))
		/*
			Param 1: Texture target
			Param 2: What option to set and for which axis
			Param 3: Wrapping mode
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		// filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		std::println("ERROR: Could not load texture {0}", pathToTexture);
	}

	stbi_image_free(data);
}
