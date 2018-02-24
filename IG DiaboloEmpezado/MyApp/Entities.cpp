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
	mesh = Mesh::generateTriPyramid(r, h, glm::dvec4(0.0, 0.0, 0.0, 1.0));
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
Diabolo::Diabolo(GLdouble r, GLdouble h) : Entity(), guardR(r), guardH(h), angle(1){}

void Diabolo::draw(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(2);	
	mesh->draw();
	glLineWidth(1);
}

void Diabolo::render(glm::dmat4 const& modelViewMat){
	this->modelViewMat = modelViewMat;
	setMvM(modelViewMat);
	dmat4 auxMat = modelViewMat * modelMat; //matriz auxiliar que transforma los vertices
	auxMat = rotate(auxMat, radians(angle), glm::dvec3(0.0, 0.0, 1.0)); //se rota
	glLoadMatrixd(value_ptr(auxMat)); // se carga
	mesh = Mesh::generateTriPyramid(guardR, guardH, glm::dvec4(1.0, 0.0, 0.0, 1.0)); // se genera la piramide que recibe las transformaciones anteriores
	draw(); //se dibuja

	auxMat = rotate(auxMat, radians(angle * 60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	mesh = Mesh::generateTriPyramid(guardR, guardH, glm::dvec4(0.0, 1.0, 0.0, 1.0));
	draw();

	auxMat = rotate(auxMat, radians(angle), glm::dvec3(0.0, 0.0, 1.0));
	auxMat = translate(auxMat,  glm::dvec3(0.0, 0.0, guardH *2));
	glLoadMatrixd(value_ptr(auxMat));
	mesh = Mesh::generateTriPyramid(guardR, -guardH, glm::dvec4(0.0, 0.0, 1.0, 1.0));
	draw();

	auxMat = rotate(auxMat, radians(angle * 60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	mesh = Mesh::generateTriPyramid(guardR, -guardH, glm::dvec4(0.0, 0.0, 0.0, 1.0));
	draw();
}


//--------------------------------------------------------------------

void Cubo::draw() {
	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
}

void Cubo::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	mesh = Mesh::generateContCubo(altura);
	draw();
	dmat4 auxMat = modelViewMat * modelMat;

	//base
	auxMat = rotate(auxMat, radians(90.0), glm::dvec3(1.0, 0.0, 0.0)); //se rota para que este en linea por donde deberia estar
	auxMat = translate(auxMat, glm::dvec3(0.0, 0.0, altura/2)); //se mueve en el ejez para ajustarla a su posicion
	glLoadMatrixd(value_ptr(auxMat));
	mesh = Mesh::generateRectangle(altura, anchura);

	auxMat = translate(auxMat, glm::dvec3(0.0, 0.0, -altura - altura/3)); //se traslada un poco en el ejez
	auxMat = translate(auxMat, glm::dvec3(-15* (altura/100), 0.0, 0.0)); //y en el x
	auxMat = rotate(auxMat, radians(45.0), glm::dvec3(0.0, 1.0, 0.0)); //para que en el eje X quede bien :P
	glLoadMatrixd(value_ptr(auxMat));
	mesh = Mesh::generateRectangle(altura, anchura);
	draw();
}

