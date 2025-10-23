#pragma once

class Texture
{
public:
	Texture(const char* pathToTexture);

	unsigned int id;

private:
	int width, height, nrChannels;
};