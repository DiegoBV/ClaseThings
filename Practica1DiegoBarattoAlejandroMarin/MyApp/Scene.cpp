#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);

  
  camera->setAZ();
  angle = 1;
  luz1 = new Light();

  GLfloat dir [3] = { 2.0, 1.0, -4.0 };

  luz2 = new SpotLight(dir);
  luz1->enable();
  glm::fvec3 vdir{ 0.0, 0.0, -1.0 };
  luz1->setDir(vdir);
  luz2->enable();
 
 
  // lights
  // textures  

  // objets

  /*objetos.push_back(new ContCube(100.0, 100, 100));/*

  objetos.push_back(new TriangleRGB(100.0));

  objetos.push_back(new EjesRGB(200.0));

  objetos.push_back(new TriPyramid(200.0, -500.0));

  //objetos.push_back(new Triangle(400.0));

  //objetos.push_back(new Dragon(3000));
  *//*aux = new Diabolo(30.0, 50.0, 150.0, 50.0);
  objetos.push_back(aux);/*
  objetos.push_back(new Cubo(150, 150));
  objetos.push_back(new Poliespiral(glm::dvec2(0.0, 0.0), 0.0, 45, 1, 1, 50));*/
  //objetos.push_back(new RectangleText(400.0, 225, 1, 1));
  //objetos.push_back(new TriPyramidText(100, 200));
  /*help = new RectangleTextPhoto(200, 100, 1, 1, camera->getVP()->getW(), camera->getVP()->getH());
  objetos.push_back(new Cubo(150, 150));
  objetos.push_back(help);
  objetos.push_back(new SueloText(2400, 2250, 20, 20));
  pot = new GlassPot(150, 500, 50.0, 80);
  objetos.push_back(pot);*/

  glm::dmat4 matrix(1.0);
  matrix = translate(matrix, glm::dvec3(300, 0, 0));
  objetos.push_back(new Esfera(matrix));
  matrix = translate(matrix, glm::dvec3(-550, 0, 0));
  objetos.push_back(new Esfera(matrix));
  matrix = translate(matrix, glm::dvec3(350, 200, 0));
  objetos.push_back(new Esfera(matrix));
  matrix = glm::dmat4(1.0);
  objetos.push_back(new EsferaLuz(matrix));
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
	
	  luz2->setDir(camera->getLook());
	  luz2->setPos(camera->getEye());
	  luz2->load(camera->getViewMat());

	  luz1->load(camera->getViewMat());

	for each (Entity* it in objetos)
	{
		if (objetos.size() > 3 && change){
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
void Scene::shutSpot()
{
	if (luz2->isOn())
		luz2->disable();
	else
		luz2->enable();
}
void Scene::shutLight()
{
	if (luz1->isOn())
		luz1->disable();
	else
		luz1->enable();
}
//-------------------------------------------------------------------------
