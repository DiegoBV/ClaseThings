//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

  virtual void render(glm::dmat4 const& modelViewMat);
  
protected:
  Mesh* mesh = nullptr;
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
public:
	ContCube(GLdouble l);
	~ContCube() { };
	virtual void draw();
};

class Dragon : public Entity
{
public:
	Dragon(GLuint numVertices);
	~Dragon() { };
	virtual void draw();
};

class Diabolo : public Entity
{
protected: 
	GLdouble guardR; 
	GLdouble guardH;
	GLdouble angle;
	glm::dmat4 modelViewMat;
public:
	Diabolo(GLdouble r, GLdouble h);
	~Diabolo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	void setAngle(GLdouble nAngle) { angle = nAngle; };
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_