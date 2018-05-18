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
	mat.load();
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
ContCube::ContCube(GLdouble l, GLdouble x, GLdouble y) : Entity(), l(l), x(x), y(y){
	mesh = Mesh::generateContCubo(l);
	texture.load("..\\Bmps\\Zelda.bmp");
	texture2.load("..\\Bmps\\emopng.bmp");
}

void ContCube::draw(){
	texture.bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glLineWidth(3);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	glDisable(GL_CULL_FACE);
	texture.unbind();

	texture2.bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glLineWidth(3);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	glDisable(GL_CULL_FACE);
	texture2.unbind();

}
void ContCube::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	dmat4 axMat = modelViewMat * modelMat;
	axMat = translate(axMat, glm::dvec3(x, l/2, 0.0));
	glLoadMatrixd(value_ptr(axMat));
	draw();
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
Diabolo::Diabolo(GLdouble r, GLdouble h, GLdouble x, GLdouble y) : Entity(), guardR(r), guardH(h), angle(1), x(x), y(y) {
	texture.load("..\\Bmps\\Zelda.bmp");
	mesh = Mesh::generateTriPyramidText(guardR, guardH);	
}

void Diabolo::draw(){
	texture.bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPointSize(2);	
	mesh->draw();
	glLineWidth(1);
	texture.unbind();
}
void Diabolo::update(GLuint timeElapsed) {
	angle = mod(angle + 0.0005*timeElapsed, 360.0);
}
void Diabolo::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	dmat4 auxMat = modelViewMat * modelMat;

	auxMat = translate(auxMat, glm::dvec3(x, y, 0.0));

	auxMat = translate(auxMat, glm::dvec3(0.0, 0.0, -guardH));
	auxMat = rotate(auxMat, radians(angle), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	//this->mesh->changeColor(this->mesh, glm::dvec4(1.0, 0.0, 0.0, 1.0));
	draw();

	auxMat = rotate(auxMat, radians(60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	//this->mesh->changeColor(this->mesh, glm::dvec4(0.0, 1.0, 0.0, 1.0));
	draw();

	auxMat = scale(auxMat, glm::dvec3(-1.0, -1.0, -1.0));
	auxMat = translate(auxMat, glm::dvec3(0.0, 0.0, -2 * guardH));
	auxMat = rotate(auxMat, radians(60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	//this->mesh->changeColor(this->mesh, glm::dvec4(0.0, 0.0, 1.0, 1.0));
	draw();

	auxMat = rotate(auxMat, radians(60.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(auxMat));
	//this->mesh->changeColor(this->mesh, glm::dvec4(0.0, 0.0, 0.0, 1.0));
	draw();

}


//--------------------------------------------------------------------

void Cubo::draw() {
	texture.bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glLineWidth(3);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	glDisable(GL_CULL_FACE);
	texture.unbind();

	texture2.bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glLineWidth(3);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	glDisable(GL_CULL_FACE);
	texture2.unbind();
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
	mesh = Mesh::generateRectangleText(altura, anchura, 0, 0);
	draw();

	//tapa
	auxMat = translate(auxMat, glm::dvec3(0.0, 0.0, -altura - altura/3)); //se traslada un poco en el ejez
	auxMat = translate(auxMat, glm::dvec3(-15* (altura/100), 0.0, 0.0)); //y en el x
	auxMat = rotate(auxMat, radians(225.0), glm::dvec3(0.0, 1.0, 0.0)); //para que en el eje X quede bien :P
	glLoadMatrixd(value_ptr(auxMat));
	mesh = Mesh::generateRectangleText(altura, anchura, 0, 0);
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

RectangleText::RectangleText(GLdouble w, GLuint h, GLuint x, GLuint y) {
	mesh = Mesh::generateRectangleText(w, h, x, y);
	//texture.load("..\\Bmps\\Zelda.bmp");

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

	texture.load("..\\Bmps\\emopng.bmp");
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

//------------------------------------------------------------------
SueloText::SueloText(GLdouble w, GLuint h, GLuint x, GLuint y) {
	mesh = Mesh::generateRectangleText(w, h, x, y);
	texture.load("..\\Bmps\\baldosaC.bmp");
}

void SueloText::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	auxMat = modelViewMat * modelMat;

	auxMat = translate(auxMat, glm::dvec3(0.0, -76, 0.0));
	auxMat = rotate(auxMat, radians(90.0), glm::dvec3(1.0, 0.0, 0.0));

	glLoadMatrixd(value_ptr(auxMat));
	draw();
}


void SueloText::draw() {
	texture.bind();
	mesh->draw();
	texture.unbind();
}

//------------------------------------------------------------------
void RectangleTextPhoto::draw() {
	texture.bind();
	mesh->draw();
	texture.unbind();
}
void RectangleTextPhoto::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	glm::dmat4 auxMat = modelViewMat * modelMat;

	auxMat = translate(auxMat, glm::dvec3(200.0, -66, 0.0));
	auxMat = rotate(auxMat, radians(-90.0), glm::dvec3(1.0, 0.0, 0.0));

	glLoadMatrixd(value_ptr(auxMat));
	draw();
}

//---------------------------------------------------------------------------------------

GlassPot::GlassPot(GLdouble l, GLdouble x, GLdouble y, GLubyte alpha) : Entity(), l(l), x(x), y(y) {
	mesh = Mesh::generateContCubo(l);
	texture.load("..\\Bmps\\window.bmp", alpha);

	GLdouble aux = sqrt(2 * (l * l));

	grass = new Grass(aux, l, 1, 1, 0);
}

void GlassPot::draw() {
	texture.bind();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLineWidth(3);
	glDepthMask(GL_FALSE);
	mesh->draw();
	glDepthMask(GL_TRUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	glDisable(GL_BLEND);
	texture.unbind();
}
void GlassPot::render(glm::dmat4 const& modelViewMat) {
	grass->render(modelViewMat);
	setMvM(modelViewMat);
	dmat4 axMat = modelViewMat * modelMat;
	axMat = translate(axMat, glm::dvec3(x, 0.0, 0.0));
	glLoadMatrixd(value_ptr(axMat));
	draw();
}

//--------------------------------------------------------------------

Grass::Grass(GLdouble w, GLuint h, GLuint x, GLuint y, GLubyte alpha) {
	mesh = Mesh::generateRectangleText(w, h, x, y);
	texture.load("..\\Bmps\\grass.bmp", ivec3(0.0, 0.0, 0.0), alpha);
}

void Grass::draw(){
	texture.bind();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLineWidth(3);
	glDepthMask(GL_FALSE);
	mesh->draw();
	glDepthMask(GL_TRUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	glDisable(GL_BLEND);
	texture.unbind();
}

void Grass::render(glm::dmat4 const& modelViewMat){
	setMvM(modelViewMat);
	dmat4 auxMat = modelViewMat * modelMat;

	auxMat = translate(auxMat, glm::dvec3(500.0, 0.0, 0.0));

	auxMat = rotate(auxMat, radians(-45.0), glm::dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(auxMat));

	draw();

	auxMat = rotate(auxMat, radians(-90.0), glm::dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(auxMat));

	draw();
}

//--------------------------------------------------------------------

//--------------------------------------------------------------------

Esfera::Esfera(glm::dmat4 v,std::string text, GLdouble radio, GLdouble dV, GLdouble dH): radio_(radio), dV_(dV), dH_(dH)
{
	qObj = gluNewQuadric();
	setModelMat(v);
	texture.load(text);
}

void Esfera::draw() {
	Entity::draw();
	texture.bind(GL_MODULATE);
	gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricOrientation(qObj, GLU_OUTSIDE);
	gluQuadricTexture(qObj, GL_TRUE);
	gluSphere(qObj, radio_, dV_, dH_);
	texture.unbind();
}

void Esfera::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	draw();
}

//--------------------------------------------------------------------

EsferaLuz::EsferaLuz(glm::dmat4 v, std::string text, GLdouble radio, GLdouble dV, GLdouble dH): Esfera(v, text, radio, dV, dH)
{
	GLfloat dir[3]{0.0, -1.0, 0.0};
	foco = new SpotLight(dir, 75);
	foco->setPos({ v[3].x, v[3].y, v[3].z }); //para hacer pruebas. La esfera esta situada en el (0,0,0)
	foco->enable();
}

void EsferaLuz::render(glm::dmat4 const & modelViewMat)
{
	foco->load(modelViewMat);
	Esfera::render(modelViewMat);
}

Terreno::Terreno()
{
	texture.load("..\\Bmps\\BarrenReds.bmp");
	terrainMesh = terrainMesh->generateTerrain();
}

void Terreno::draw()
{
	Entity::draw();
	texture.bind();
	terrainMesh->draw();
	texture.unbind();
}

void Terreno::render(glm::dmat4 const & modelViewMat)
{
	setMvM(modelViewMat);
	dmat4 axMat = modelViewMat * modelMat;
	axMat = translate(axMat, glm::dvec3(0.0, -400.0, 0.0));
	glLoadMatrixd(value_ptr(axMat));
	draw();
}
