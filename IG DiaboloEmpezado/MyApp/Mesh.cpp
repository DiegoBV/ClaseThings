#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
}
//-------------------------------------------------------------------------

void Mesh::draw() 
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
    }
	
    glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
  Mesh* m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------

Mesh* Mesh::generateTriangle(GLdouble r){  //Generador de triángulo equilatero
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;
	dvec3 ref = dvec3(0.0, r, 0.0);


	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = ref;
	m->vertices[1] = dvec3(0 + (r * cos(radians(210.0))), 0 + (r* sin(radians(210.0))), 0.0);
	m->vertices[2] = dvec3(0 + (r * cos(radians(330.0))), 0 + (r* sin(radians(330.0))), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);

	return m;
}

//--------------------------------------------------------------------------

Mesh* Mesh::generateTriangleRGB(GLdouble r){  //Generador de triángulo equilatero
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;
	dvec3 ref = dvec3(0.0, r, 0.0);


	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = ref;
	m->vertices[1] = dvec3(0 + (r * cos(radians(210.0))), 0 + (r* sin(radians(210.0))), 0.0);
	m->vertices[2] = dvec3(0 + (r * cos(radians(330.0))), 0 + (r* sin(radians(330.0))), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generateTriPyramid(GLdouble r, GLdouble h, dvec4 c){
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, 0.0, h);
	m->vertices[1] = dvec3(0.0, r, 0.0);
	m->vertices[2] = dvec3(0 + (r * cos(radians(210.0))), 0 + (r* sin(radians(210.0))), 0.0);
	m->vertices[3] = dvec3(0 + (r * cos(radians(330.0))), 0 + (r* sin(radians(330.0))), 0.0);
	m->vertices[4] = dvec3(0.0, r, 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = c;
	m->colors[1] = c;
	m->colors[2] = c;
	m->colors[3] = c;
	m->colors[4] = c;

	return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generateContCubo(GLdouble l){
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(-l/2, l, l/2);
	m->vertices[1] = dvec3(-l/2, 0.0, l/2);
	m->vertices[2] = dvec3(l / 2, l, l / 2);
	m->vertices[3] = dvec3(l / 2, 0.0, l / 2);
	m->vertices[4] = dvec3(l/2, l, -l/2);
	m->vertices[5] = dvec3(l/2, 0.0, -l /2);
	m->vertices[6] = dvec3(-l / 2, l, -l / 2);
	m->vertices[7] = dvec3(-l/2, 0.0, -l/2);
	m->vertices[8] = dvec3(-l / 2, l, l / 2);
	m->vertices[9] = dvec3(-l / 2, 0.0, l / 2);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[3] = dvec4(0.0, 0.0, 0.0, 0.0);

	return m;
}

//--------------------------------------------------------------------------

Mesh* Mesh::generaDragon(GLuint numVert){
	Mesh* m = new Mesh();
	double azar; 
	double pr1 = 0.787473;
	double pr2 = 0.212527;
	double x = 0.0;
	double y = 0.0;

	m->type = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];
	m->colors = new dvec4[m->numVertices];

	m->vertices[0] = dvec3(0.0, 0.0, 0.0);
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);

	//Ahora hacemos el bucle que dibujará al dragón
	for (int i = 1; i < numVert; i++){
		azar = rand() / double(RAND_MAX);

		if (azar < pr1){
			m->vertices[i] = dvec3(0.824074 * x + 0.281482 * y - 0.882290, -0.212346 * x + 0.864198 * y - 0.110607, 0.0);
		}
		else {
			m->vertices[i] = dvec3(0.088272 * x + 0.520988 * y + 0.785360, -0.463889 * x - 0.377778 * y + 8.095795, 0.0);
		}

		m->colors[i] = dvec4(0.0, 0.0, 0.0, 0.0);

		x = m->vertices[i].x;
		y = m->vertices[i].y;
	}

	return m;
}

