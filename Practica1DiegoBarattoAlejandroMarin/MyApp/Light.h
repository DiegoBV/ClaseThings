#pragma once
#include <GL/freeglut.h>
#include <gtc/type_ptr.hpp>

class Light {
protected:
	static GLuint cont; // valor inicial cont = 0
	GLuint id = GL_MAX_LIGHTS; // GL_LIGHTi
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };
	bool on = false;
public:
	Light() {
		if (cont < GL_MAX_LIGHTS) {
			id = GL_LIGHT0 + cont;
			++cont;
			glEnable(id);
		}
	};
	virtual void load(glm::dmat4 const& modelViewMat);
	~Light() { disable(); }
	void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) { glDisable(id); on = false; } };
	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) { glEnable(id); on = true; } };
	void setPos(glm::fvec3 pos) { posDir = glm::fvec4(pos, 1.0); };
	void setDir(glm::fvec3 dir) { posDir = glm::fvec4(-dir, 0.0); };
	void setAmb(glm::fvec4 amb) {};
	bool isOn() const { return on; };
};

class SpotLight : public Light {
protected:
	GLfloat dir[3] = { 0.0, 0.0, 0.0 };

public:
	SpotLight() {};

	SpotLight(GLfloat dir[], GLfloat angle = 45.0) : Light() {
		this->dir[0] = dir[0];
		this->dir[1] = dir[1];
		this->dir[2] = dir[2];
		glLightf(id, GL_SPOT_CUTOFF, angle);
		glLightf(id, GL_SPOT_EXPONENT, 4);
		glLightfv(id, GL_SPOT_DIRECTION, dir);
	}

	virtual void load(glm::dmat4 const& modelViewMat) {
		Light::load(modelViewMat);
	}
};

