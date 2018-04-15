#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

 void Viewport::setSize(GLsizei aw, GLsizei ah) 
 { 
   w = aw; 
   h = ah; 
   set(); 
 }
 //-------------------------------------------------------------------------

 void Viewport::set() 
 { 
   glViewport(x, y, w, h);
 }
//-------------------------------------------------------------------------

 void Viewport::setPosition(int xX, int yY){
	 x = xX; 
	 y = yY;
	 set();
 }

void Camera::setAZ() 
{
  eye= dvec3(0, 0, 500);
  look= dvec3(0, 0, 0);
  up= dvec3(0, 1, 0);
  viewMat = lookAt(eye, look, up);
  pitch_ = 0;
  yaw_ = 0;
  update();
  setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
  eye= dvec3(500, 500, 500);
  look= dvec3(0, 10, 0);
  up= dvec3(0, 1, 0);
  update();
  glm::dvec3 front = -n;
  viewMat = lookAt(eye, look, up);
  pitch_ = degrees(asin(front.y));
  yaw_ = degrees(asin(front.x / (cos(radians(pitch_)))));
  setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}

void Camera::moveLR(GLdouble cs)
{
	eye = eye + (u * cs);
	look = look + (u*cs);
	viewMat = lookAt(eye, look, up);
	update();
}

void Camera::moveFB(GLdouble cs)
{
	eye = eye + ((-n) * cs);
	look = look + ((-n)*cs);
	viewMat = lookAt(eye, look, up);
	update();
}

void Camera::moveUD(GLdouble cs)
{
	eye = eye + (v * cs);
	look = look + (v*cs);
	viewMat = lookAt(eye, look, up);
	update();
}

void Camera::update() {
	n = normalize(eye - look);
	u = normalize(cross(up, n));
	v = cross(n, u);
}
void Camera::changeView()
{
	if (ortho_) {
		ortho_ = false;
		setPM();
	}
	else {
		ortho_ = true;
		setPM();
	}
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
  if (ortho_) {
	  glMatrixMode(GL_PROJECTION);
	  projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, 2 * yTop, farVal);

	  glLoadMatrixd(value_ptr(projMat));
	  glMatrixMode(GL_MODELVIEW);
  }
  else {
	  glMatrixMode(GL_PROJECTION);
	  projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	  glLoadMatrixd(value_ptr(projMat));
	  glMatrixMode(GL_MODELVIEW);
  }
}
//-------------------------------------------------------------------------

void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw){
	pitch_ += incrPitch;
	yaw_ += incrYaw;

	if (pitch_ > 89.5) pitch_ = 89.5;
	if (yaw_ > 89.5) yaw_ = 89.5;

	glm::dvec3 front = -n;

	front.x = sin(radians(yaw_)) * cos(radians(pitch_)); //actualizamos la direccion de vista
	front.y = sin(radians(pitch_));
	front.z = -cos(radians(yaw_)) * cos(radians(pitch_)); //formulitas de los apntes
	front = glm::normalize(front);
	look = eye + front; //importante modificar el look para que los demas metodos funcionen bien
	viewMat = lookAt(eye, look, up);
	n = -front;

	update(); //update de vectores
}


