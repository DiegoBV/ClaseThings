#pragma once
#include "Pixmap32RGBA.h"
#include <GL/freeglut.h>
#include <glm.hpp>

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
	bool load(const std::string & BMP_Name, glm::ivec3 color, GLubyte alpha);

	void bind(GLuint mix = GL_REPLACE);

	void unbind() 
	{ 
		glBindTexture(GL_TEXTURE_2D, 0); 
	}
	void loadColorBuffer(GLsizei width, GLsizei height);
	void save(const std::string & BMP_Name);
	void wrap(GLuint wp = GL_CLAMP);
};

