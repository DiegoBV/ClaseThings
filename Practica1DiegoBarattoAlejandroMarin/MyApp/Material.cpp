#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
}

void Material::load() {
	glMaterialf(face, GL_SHININESS, expF);
	glMaterialfv(face, GL_EMISSION, color);
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glShadeModel(sh);
}
