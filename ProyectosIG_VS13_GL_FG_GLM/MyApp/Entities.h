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

//-------------------------------------------------------------------------

class Triangle : public Entity
{
public:
	Triangle(GLdouble r);
	~Triangle() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class TriangleRGB : public Entity
{
public:
	TriangleRGB(GLdouble r);
	~TriangleRGB() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class TriPyramid : public Entity
{
public:
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class ContCubo : public Entity
{
public:
	ContCubo(GLdouble l);
	~ContCubo() { };
	virtual void draw();
};

#endif //_H_Entities_H_