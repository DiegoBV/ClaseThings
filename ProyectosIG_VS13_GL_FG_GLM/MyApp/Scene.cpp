#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  
  camera->setAZ();
    
  // lights
  // textures  

  // objets
  //objetos.push_back(new EjesRGB(200.0));
  //objetos.push_back(new Triangle(200.0));
  //objetos.push_back(new TriangleRGB(100.0));
  //objetos.push_back(new TriPyramid(100.0, 200.0));
  //objetos.push_back(new ContCubo(100.0));
  objetos.push_back(new Dragon(3000));
  
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
  glMatrixMode(GL_MODELVIEW);

	for each (Entity* it in objetos)
	{
		it->render(camera->getViewMat());
	}
}
//-------------------------------------------------------------------------

