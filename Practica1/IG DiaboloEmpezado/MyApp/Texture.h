#pragma once
#include "Pixmap32RGBA.h"

class Texture
{
protected:
	GLuint w, h;
	GLuint id;

	void init();

public:
	Texture() : w(0), h(0), id(0) {}
	~Texture();

	bool load(const std::string &BMP_Name, GLubyte alpha = 255);

	void bind();

	void unbind() 
	{ 
		glBindTexture(GL_TEXTURE_2D, 0); 
	}
	void loadColorBuffer(GLsizei width, GLsizei height);
	void save(const std::string & BMP_Name);
};

