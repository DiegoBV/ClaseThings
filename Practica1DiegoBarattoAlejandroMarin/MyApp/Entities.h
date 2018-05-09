//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
#include <string>

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

  virtual void render(glm::dmat4 const& modelViewMat);
  virtual void update(GLuint timeElapsed) {};

  void setModelMat(glm::dmat4 const& mMat) { modelMat = mMat; }
  void setMaterial(Material const& mt) { mat = mt; }
  void setTexture(Texture const& tex) { texture = tex; };
  
protected:
  Mesh* mesh = nullptr;
  Texture texture;
  Texture texture2;
  Material mat;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);

};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};


class Triangle : public Entity
{
public:
	Triangle(GLdouble r);
	~Triangle() { };
	virtual void draw();
};

class TriangleRGB : public Entity
{
public:
	TriangleRGB(GLdouble r);
	~TriangleRGB() { };
	virtual void draw();
};

class TriPyramid : public Entity
{
public:
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
};

class ContCube : public Entity
{
private:
	GLdouble l, x, y;
public:
	ContCube(GLdouble l, GLdouble x, GLdouble y);
	~ContCube() { };
	virtual void draw();
	void render(glm::dmat4 const& modelViewMat);
};

class Dragon : public Entity
{
private:
	GLuint numVertices;
public:
	Dragon(GLuint numVertices);
	~Dragon() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

class Diabolo : public Entity
{
protected: 
	GLdouble guardR; 
	GLdouble guardH;
	GLdouble angle;
	GLdouble x, y;
	glm::dmat4 modelViewMat;
public:
	Diabolo(GLdouble r, GLdouble h, GLdouble x, GLdouble y);
	~Diabolo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update(GLuint timeElapsed);
	void setAngle(GLdouble nAngle) { angle = nAngle; };
};

//-------------------------------------------------------------------------
class Cubo : public Entity
{
protected:
	GLdouble altura;
	GLdouble anchura;
public:
	Cubo(GLdouble altura, GLdouble anchura) : altura(altura), anchura(anchura) {
		texture.load("..\\Bmps\\container.bmp");
		texture2.load("..\\Bmps\\chuches.bmp");
	};
	~Cubo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() { };
	virtual void draw();
};

class RectangleText : public Entity {
public :
	RectangleText(GLdouble w, GLuint h, GLuint x, GLuint y);
	~RectangleText() { }
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	void setText(GLsizei width, GLsizei height) {
		texture.loadColorBuffer(width, height); 
	}
};

class SueloText : public Entity {
protected:
	glm::dmat4 auxMat;

public:
	SueloText(GLdouble w, GLuint h, GLuint x, GLuint y);
	~SueloText() { }
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

class TriPyramidText : public Entity {
public:
	TriPyramidText(GLdouble r, GLuint h);
	~TriPyramidText() { }
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
};

class RectangleTextPhoto : public RectangleText {
protected:
	GLsizei width; GLsizei height;
public:
	RectangleTextPhoto(GLdouble w, GLuint h, GLuint x, GLuint y, GLsizei width, GLsizei height) : RectangleText(w, h, x, y), width(width), height(height) {

	}
	~RectangleTextPhoto() { }
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	void setText(GLsizei width, GLsizei height) {
		texture.loadColorBuffer(width, height);
	}
	virtual void update(GLuint timeElapsed) { setText(width, height); };
};

class Grass : public Entity
{
private:
	int numGrass;

public:
	Grass(GLdouble w, GLuint h, GLuint x, GLuint y, GLubyte alpha);
	~Grass() { }
	virtual void draw();
	void render(glm::dmat4 const& modelViewMat);

};

class GlassPot : public Entity
{
private:
	GLdouble l;
	GLdouble x;
	GLdouble y;
	Grass* grass;
public:
	GlassPot(GLdouble l, GLdouble x, GLdouble y, GLubyte alpha);
	~GlassPot() { };
	virtual void draw();
	void render(glm::dmat4 const& modelViewMat);
};

class Esfera : public Entity
{
protected:
	GLUquadricObj* qObj;
	GLdouble radio_, dV_, dH_;
public:
	Esfera() {};
	Esfera(glm::dmat4 v, std::string text, GLdouble radio, GLdouble dV, GLdouble dH);
	virtual ~Esfera() { gluDeleteQuadric(qObj); };
	virtual void draw();
	void render(glm::dmat4 const& modelViewMat);
};

class EsferaLuz : public Esfera
{
protected:
	GLUquadricObj * qObj;
	SpotLight* foco;
public:
	EsferaLuz(glm::dmat4 v, std::string text,GLdouble radio, GLdouble dV, GLdouble dH);
	virtual ~EsferaLuz() { delete foco; };
	void render(glm::dmat4 const& modelViewMat);
	SpotLight* getFoco() {
		return foco;
	}
};



#endif //_H_Entities_H_

