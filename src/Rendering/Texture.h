#pragma once

#include "glad/glad.h"
#include <string>

class Texture
{
public:
	Texture(int width, int height);
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	void SynchronizeData();

	void UpdateData(int width, int height, const unsigned char*);
	void UpdateSubData(const unsigned char* data, int width, int height, int offsetX, int offsetY);

private:
	unsigned int m_RendererID;
	unsigned char* m_PixelBuffer;
	int m_Width, m_Height;

};
