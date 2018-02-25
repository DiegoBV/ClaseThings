#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  
  camera->setAZ();
  angle = 1;
    
  // lights
  // textures  

  // objets

  //objetos.push_back(new ContCube(100.0));

  //objetos.push_back(new TriangleRGB(100.0));

  //objetos.push_back(new EjesRGB(200.0));

  //objetos.push_back(new TriPyramid(200.0, -500.0));

  //objetos.push_back(new Triangle(400.0));

  //objetos.push_back(new Dragon(3000));
  aux = new Diabolo(30.0, 50.0);
  objetos.push_back(aux);
  objetos.push_back(new Cubo(150, 150));
  objetos.push_back(new Poliespiral(glm::dvec2(0.0, 0.0), 0.0, 45, 1, 1, 50));
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
  int i = 0;

	for each (Entity* it in objetos)
	{
		if (objetos.size() > 3){
			if (i == 0){
				camera->getVP()->setPosition((-camera->getVP()->getW() / 4), (camera->getVP()->getH() / 4));
				it->render(camera->getViewMat());
			}
			else if (i == 1){
				camera->getVP()->setPosition((camera->getVP()->getW() / 4), (camera->getVP()->getH() / 4));
				it->render(camera->getViewMat());
			}
			else if (i == 2){
				camera->getVP()->setPosition((-camera->getVP()->getW() / 4), (-camera->getVP()->getH() / 4));
				it->render(camera->getViewMat());
			}
			else{
				camera->getVP()->setPosition((camera->getVP()->getW() / 4), (-camera->getVP()->getH() / 4));
				it->render(camera->getViewMat());
			}
		}
		else {
			it->render(camera->getViewMat());
		}
		
		i++;
	}
}
//-------------------------------------------------------------------------

