#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Material
{
public:
	Material();
	~Material();
	glm::fvec4 ambient, diffuse, specular; // coeficientes de reflexi�n
	GLfloat expF; // exponente especular
	GLuint face = GL_FRONT_AND_BACK; // ambos lados
	GLuint sh = GL_SMOOTH; // smooth shading
	GLfloat color[4] = {0,0,0,1};
	virtual void load();
};

