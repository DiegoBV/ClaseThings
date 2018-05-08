#include "Texture.h"


Texture::~Texture()
{
}

void Texture::init() {
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::bind(GLuint mix) {
	glBindTexture(GL_TEXTURE_2D, id);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV, GL_REPLACE);

}

bool Texture::load(const std::string & BMP_Name, GLubyte alpha) {
	if (id == 0)
	{
		init();
	}

	PixMap32RGBA pixMap;

	pixMap.load_bmp24BGR(BMP_Name);



	if (alpha != 255) {
		pixMap.set_alpha(alpha);
	}

	w = pixMap.width();

	h = pixMap.height();

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixMap.data());

	return true;
}

bool Texture::load(const std::string & BMP_Name, glm::ivec3 color, GLubyte alpha)
{
	if (id == 0)
	{
		init();
	}

	
	PixMap32RGBA pixMap;

	pixMap.load_bmp24BGR(BMP_Name);



	if (alpha != 255) {
		PixMap32RGBA::rgba_color col;
		col.r = color.r;
		col.g = color.g;
		col.b = color.b;
		pixMap.set_colorkey_alpha(col, alpha);
	}

	w = pixMap.width();

	h = pixMap.height();

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixMap.data());

	return false;
}

void Texture::loadColorBuffer(GLsizei width, GLsizei height) {
	if (id == 0)
	{
		init();
	}

	w = width;

	h = height;


	glReadBuffer(GL_BACK);

	glBindTexture(GL_TEXTURE_2D, id);

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);
}

void Texture::save(const std::string & BMP_Name) {
	PixMap32RGBA tx;

	tx.create_pixmap(w, h);

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, tx.data());
	tx.save_bmp24BGR(BMP_Name);
}

void Texture::wrap(GLuint wp){
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);
}
