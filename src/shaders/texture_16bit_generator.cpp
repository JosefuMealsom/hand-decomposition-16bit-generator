#include "pch/pch.h"
#include "logger.h"
#include "shaders/texture_16bit_generator.h"

unsigned int Texture::generateEmpty16bitTexture(unsigned int w, unsigned int h)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	uint16_t* data = new uint16_t[w * h * 4];
	for (int i = 0; i < w * h * 4; i++)
	{
		data[i] = 0;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT, data);

	delete[] data;
	return texture_id;
}

unsigned int Texture::generateEmpty16MSAAbitTexture(unsigned int w, unsigned int h)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture_id);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16, w, h, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	return texture_id;
}


unsigned int Texture::generate16bitTexture(unsigned int w, unsigned int h)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	int channels = 4;

	int numBytes = w * h * channels;
	uint16_t* data = new uint16_t[numBytes];

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			int i = y * w * 4 + x * 4;

			data[i] = x * 10;
			data[i + 1] = y * 10;
			data[i + 2] = 0;
			data[i + 3] = 65535;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT, data);

	delete[] data;
	return texture_id;
}

unsigned int Texture::generate8bitTexture(unsigned int w, unsigned int h)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int channels = 4;

	int numBytes = w * h * channels;
	uint8_t* data = new uint8_t[w * h * 4];

	for (int i = 0; i < numBytes; i++)
	{
		data[i] = 255;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] data;

	return texture_id;
}
