#pragma once
#include "Mesh.h"
class IndexMesh :
	public Mesh
{
public:
	static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);
	IndexMesh() {
		numIndices = 0; indices = nullptr;
		type = GL_TRIANGLES;
	}
	~IndexMesh() { delete[] indices; };
	virtual void draw();
	void enable();
	void disable();
	IndexMesh* generateTerrain();

private:
	GLuint * indices = nullptr;
	GLuint numIndices = 0;
};

