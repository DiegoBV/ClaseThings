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
	texture.load("..\\Bmps\\Zelda.bmp");
}

void ContCube::draw(){
	texture.bind();
	glLineWidth(3);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	texture.unbind();
}

//--------------------------------------------------------------------
Dragon::Dragon(GLuint numVertices) : Entity(), numVertices(numVertices){}

void Dragon::draw(){
	glPointSize(2);
	mesh->draw();
	glLineWidth(1);
}

void Dragon::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	dmat4 axMat = modelViewMat * modelMat;
	axMat = translate(axMat, glm::dvec3(-40.0, -170.0, 0.0));
	axMat = scale(axMat, glm::dvec3(40.0, 40.0, 0.0));
	glLoadMatrixd(value_ptr(axMat));
	mesh = Mesh::generaDragon(numVertices);
	draw();
}

//--------------------------------------------------------------------
Diabolo::Diabolo(GLdouble r, GLdouble h) : Entity(), guardR(r), guardH(h), angle(1){ mesh = Mesh::generateTriPyramid(guardR, guardH); }

void Diabolo::draw(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(2);	
	mesh->draw();
	glLineWidth(1);
}

void Diabolo::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	dmat4 auxMat = modelViewMat * modelMat;
	auxMat = translate(auxMat, glm::dvec3(0.0, 0.0, -guardH));
	auxMat = rotate(auxMat, radians(angle), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	this->mesh->changeColor(this->mesh, glm::dvec4(1.0, 0.0, 0.0, 1.0));
	draw();

	auxMat = rotate(auxMat, radians(60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	this->mesh->changeColor(this->mesh, glm::dvec4(0.0, 1.0, 0.0, 1.0));
	draw();

	auxMat = scale(auxMat, glm::dvec3(-1.0, -1.0, -1.0));
	auxMat = translate(auxMat, glm::dvec3(0.0, 0.0, -2 * guardH));
	auxMat = rotate(auxMat, radians(60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	this->mesh->changeColor(this->mesh, glm::dvec4(0.0, 0.0, 1.0, 1.0));
	draw();

	auxMat = rotate(auxMat, radians(60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	this->mesh->changeColor(this->mesh, glm::dvec4(0.0, 0.0, 0.0, 1.0));
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

//--------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity() {
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}

void Poliespiral::draw() {
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
}

//--------------------------------------------------------------------

RectangleText::RectangleText(GLdouble w, GLuint h) {
	mesh = Mesh::generateRectangleText(w, h);

	texture.load("..\\Bmps\\Zelda.bmp");
}

void RectangleText::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	draw();
}


void RectangleText::draw() {
	texture.bind();
	mesh->draw();
	texture.unbind();
}

//--------------------------------------------------------------------

TriPyramidText::TriPyramidText(GLdouble r, GLuint h) {
	mesh = Mesh::generateTriPyramidText(r, h);

	texture.load("..\\Bmps\\Zelda.bmp");
}

void TriPyramidText::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	draw();
}


void TriPyramidText::draw() {
	texture.bind();
	mesh->draw();
	texture.unbind();
}

