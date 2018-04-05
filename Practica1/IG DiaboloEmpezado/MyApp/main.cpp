//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "Camera.h"
#include "Scene.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    

// Scene entities
Scene scene(&camera);   

Texture foto;
GLuint last_update_tick;

//mouse
glm::dvec2 mCoord; 

//----------- Callbacks ----------------------------------------------------

void display();
void update();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
bool stopAnim = false;

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{

  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition (140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL  
  
  int win = glutCreateWindow( "Freeglut-project" );  // window's identifier
  
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutIdleFunc(update);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
 
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';
 
  scene.init();    // after creating the context
   
  glutMainLoop(); 
    
  //cin.sync();   cin.get();
  glutDestroyWindow(win);  // Destroy the context 

  return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffer
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
  scene.render();   
    
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void update() {
	if (!stopAnim) {
		if (last_update_tick < glutGet(GLUT_ELAPSED_TIME) + 10000) {
			last_update_tick = glutGet(GLUT_ELAPSED_TIME) + 10000;
			scene.update(glutGet(GLUT_ELAPSED_TIME));
			display();
			camera.update();
		}
	}
}

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.setSize(newWidth, newHeight);  
  // Resize Scene Visible Area 
  camera.setSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.scale(+0.01);   // zoom in  
    break;
  case '-':
    camera.scale(-0.01);   // zoom out
    break;
  case 'l':
	  camera.set3D(); 
	  break;
  case 'o':
	  camera.setAZ();
	  break;
  case 'a':
	  camera.moveLR(-20.0); //izquierda
	 break;
  case 'd':
	  camera.moveLR(20.0); //derecha
	  break;
  case 'w':
	  camera.moveUD(20.0); //arriba
	  break;
  case 's':
	  camera.moveUD(-20.0); //abajo
	  break;
  case 'z':
	  camera.moveFB(20.0); //delante
	  break;
  case 'x':
	  camera.moveFB(-20.0); //detrás
	  break;
  case 'f':
	  stopAnim = !stopAnim;
	  /*foto.loadColorBuffer(viewPort.getW(), viewPort.getH());
	  foto.save("..\\Bmps\\prueba.bmp");
	  scene.help->setText(viewPort.getW(), viewPort.getH());*/
	  break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    camera.pitch(1);   // rotate 1 on the X axis
    break;
  case GLUT_KEY_LEFT:
    camera.yaw(1);     // rotate 1 on the Y axis 
    break;
  case GLUT_KEY_UP:
    camera.roll(1);    // rotate 1 on the Z axis
    break;
  case GLUT_KEY_DOWN:
    camera.roll(-1);   // rotate -1 on the Z axis
    break;
  default:
    need_redisplay = true;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------
void mouse(int button, int state, int x, int y){
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}

//-------------------------------------------------------------------------
void motion(int x, int y){
	glm::dvec2 mOffset = mCoord;
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	mOffset = (mCoord - mOffset) * 0.05; // sensitivity = 0.05
	camera.rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();
}
