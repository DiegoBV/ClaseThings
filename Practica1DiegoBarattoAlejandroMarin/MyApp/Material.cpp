#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
}

void Material::load() {
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glShadeModel(sh);
}
