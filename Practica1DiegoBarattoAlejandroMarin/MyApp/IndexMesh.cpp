#include "IndexMesh.h"
#include <fstream>
#include <GL/freeglut.h>
#include <glm.hpp>

void IndexMesh::enable() {
	Mesh::enable(); // glEnableClientState(…), glXXXPointer(…)
	if (indices != nullptr) {
		glEnableClientState(GL_INDEX_ARRAY);
		glIndexPointer(GL_UNSIGNED_INT, 0, indices);
	}
}

void IndexMesh::disable() {
	Mesh::disable(); // glDisableClientState(…)
	glDisableClientState(GL_INDEX_ARRAY);
}

void IndexMesh::draw() { //??????

	enable();
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices);
	disable();
}

IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint numDiv) {	
	// grid cuadrado de lado*lado, centrado en el plano Y=0,
	// dividido en numDiv*numDiv celdas
	IndexMesh* m = new IndexMesh();
	GLdouble incr = lado / numDiv; // incremento para la coordenada x, y la z
	GLuint numVer = numDiv + 1; // num. de vértices por filas y por columnas
								// generar vértices

	m->numVertices = numVer * numVer; // num. de vértices
	m->vertices = new glm::dvec3[m->numVertices];

	for (unsigned int i = 0; i < numDiv; i++) {
		for (unsigned int j = 0; j < numDiv; j++) {
			m->vertices[j] = glm::dvec3(-lado/2 + incr*j, 0, -lado/2 + incr*i); //makes sense maybe
		}
	}

	// generar índices
	m->numIndices = numDiv * numDiv * 6; ; // num. de índices
	m->indices = new GLuint[m->numIndices];

	int i = 0;
	for (unsigned int f = 0; f < numDiv; f++) {
		for (unsigned int c = 0; c < numDiv; c++) {
			GLdouble iv = f*numVer + c;
			//----Triangulo 1 -----
			//i = 0
			m->indices[i++] = iv; 
			// i = 1
			m->indices[i++] = iv + numVer;
			//i = 2
			m->indices[i++] = iv + 1;
			//i = 3
			//----Triangulo 2-----
			m->indices[i++] = iv + 1;
			//i = 4
			m->indices[i++] = iv + numVer;
			//i = 5
			m->indices[i++] = iv + numVer + 1;
			//i = 6
		}
	}
	return m;
}

IndexMesh* IndexMesh::generateTerrain() {
	std::ifstream file("..\\Bmps\\terrain.raw", std::ios::binary); // open
	if (!file.is_open()) return nullptr; // "terrain.raw": 257*257 unsigned chars
	GLuint nDiv = 256; // nVer=257.
	GLdouble lado = nDiv * 8; // para incr=8
	GLuint numVer = nDiv + 1; // num. de vértices por filas y por columnas

	IndexMesh* m = generateGrid(lado, nDiv);
	unsigned char * data = new unsigned char[m->numVertices];
	file.read((char *)data, m->numVertices * sizeof(char));
	file.close(); // char = byte -> leer en data un bloque de numVertices bytes

	// modificar la coordenada Y de los vértices con los datos de data (*0.5)
	for (unsigned int i = 0; i < m->numVertices; i++) {
		m->vertices[i] *= data[i];
	}

	// generar coordenadas de textura -> recorrido de vértices
	GLdouble incr = 1 / nDiv; // incremento para la coordenada x, y la z (textura)

	m->textCoords = new glm::dvec2[m->numVertices];
	for (unsigned int f = 0; f < nDiv; f++) {
		for (unsigned int c = 0; c < nDiv; c++) {
			m->textCoords[f * numVer + c] = glm::dvec2(0 + incr*c, 1 - incr*f);
		}
	}

	delete data;
	// generar normales -> recorrido de triángulos
	m->normals = new glm::dvec3[m->numVertices];

	for (unsigned int i = 0; i < m->numVertices; i++) {
		m->normals[i] = glm::dvec3(0, 0, 0); //reset a 0
	}

	int ind = 0;
	for (int i = 0; i < m->numVertices; i++) {
		
		int a = m->indices[ind++];
		int b = m->indices[ind++];
		int c = m->indices[ind++];

		glm::dvec3 vAux1 = {m->vertices[c] - m->vertices[b]};
		glm::dvec3 vAux2 = {m->vertices[a] - m->vertices[b]}; //obtener los vectores del triangulo

		glm::dvec3 n = cross(vAux1, vAux2);

		m->normals[a] += n; //sumamos n a los normales de cada vertice
		m->normals[b] += n;
		m->normals[c] += n;
	}

	for (unsigned int i = 0; i < m->numVertices; i++) {
		m->normals[i] = normalize(m->normals[i]);
	}

	return m;
}
