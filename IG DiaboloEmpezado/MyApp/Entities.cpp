#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------

Triangle::Triangle(GLdouble r) : Entity(){
	mesh = Mesh::generateTriangle(r);
}

void Triangle::draw(){
	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
}

//-----------------------------------------------------------------------

TriangleRGB::TriangleRGB(GLdouble r) : Entity(){
	mesh = Mesh::generateTriangleRGB(r);
}

void TriangleRGB::draw(){
	glLineWidth(3);
	mesh->draw();
	glLineWidth(1);
}

//---------------------------------------------------------------------
TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity(){
	mesh = Mesh::generateTriPyramid(r, h);
}

void TriPyramid::draw(){
	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
}

//--------------------------------------------------------------------
ContCube::ContCube(GLdouble l) : Entity(){
	mesh = Mesh::generateContCubo(l);
}

void ContCube::draw(){
	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
}

//--------------------------------------------------------------------
Dragon::Dragon(GLuint numVertices) : Entity(){
	mesh = Mesh::generaDragon(numVertices);
}

void Dragon::draw(){
	glPointSize(2);
	mesh->draw();
	glLineWidth(1);
}

//--------------------------------------------------------------------
Diabolo::Diabolo(GLdouble r, GLdouble h) : Entity(){
	mesh = Mesh::generateTriPyramid(r, h);
}

void Diabolo::draw(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(2);
	mesh->draw();
	glLineWidth(1);
}

void Diabolo::render(glm::dmat4 const& modelViewMat){

	setMvM(modelViewMat);
	dmat4 auxMat = modelViewMat * modelMat;
	auxMat = rotate(auxMat, radians(0.0), glm::dvec3(0.0, 0.0, 1.0));
	modelMat = auxMat;
	draw();
	auxMat = rotate(auxMat, radians(45.0), glm::dvec3(0.0, 0.0, 1.0));
	modelMat = auxMat;
	draw();
	/*for (int i = 0; i < 2; i++){
		rotate(dmat4(1), radians(45.0 * i), glm::dvec3(0.0, 0.0, 1.0));
		draw();
	}*/
}

