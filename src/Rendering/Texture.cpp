#include "Texture.h"
#include "stb_image/stb_image.h"
#include <iostream>

// This is intended for generated/procedural textures.
Texture::Texture(int width, int height) : m_RendererID(0), m_PixelBuffer(nullptr), m_Width(width), m_Height(height)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_PixelBuffer = new unsigned char[m_Width * m_Height * 4];
	for (int i = 0; i < m_Width * m_Height * 4; i += 4) {
		m_PixelBuffer[i]	 = 255;  // Red
		m_PixelBuffer[i + 1] = 0;    // Green
		m_PixelBuffer[i + 2] = 255;  // Blue
		m_PixelBuffer[i + 3] = 255;  // Alpha
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_PixelBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& path) : m_RendererID(0), m_PixelBuffer(nullptr), m_Width(0), m_Height(0)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, 0, 4);

	if (data)
	{
		m_PixelBuffer = new unsigned char[m_Width * m_Height * 4];
		std::copy(data, data + m_Width * m_Height * 4, m_PixelBuffer);

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_PixelBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Failed to load texture: " << path << std::endl;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
	delete[] m_PixelBuffer;
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Using UpdateSubData doesnt adjust the local buffer(m_PixelBuffer) so use this to set m_PixelBuffer to whats on the GPU.
void Texture::SynchronizeData()
{
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_PixelBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UpdateData(int width, int height, const unsigned char* data)
{
	m_Width = width;
	m_Height = height;

	delete[] m_PixelBuffer;
	m_PixelBuffer = new unsigned char[m_Width * m_Height * 4];
	std::copy(data, data + m_Width + m_Height * 4, m_PixelBuffer);

	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Texture::UpdateSubData(const unsigned char* data, int width, int height, int offsetX, int offsetY)
{
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}