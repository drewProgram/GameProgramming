#pragma once

enum class EFileTypes
{
	PNG,
	JPG
};

class Texture
{
public:
	Texture(const char* pathToTexture, EFileTypes _fileType);

	unsigned int id;

private:
	int width, height, nrChannels;

	EFileTypes fileType;
};