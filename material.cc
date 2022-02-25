#include "material.h"
#include <iostream>
#include <vector>

// Sirve simplemente para convertir las tuplas de float a arrays GLfloat
// (rellena un array[4] con el contenido de una tupla)
void conversionGLF(Tupla4f src, std::vector<GLfloat>& dst) {
    dst.clear();
    for (int i=0; i<4; ++i) {
        dst.push_back(src(i));
    }
}

void Material::aplicar() const {
    std::vector<GLfloat> convertidos;
    conversionGLF(this->difuso, convertidos);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, convertidos.data());
    conversionGLF(this->especular, convertidos);
    glMaterialfv(GL_FRONT, GL_SPECULAR, convertidos.data());
    conversionGLF(this->ambiente, convertidos);
    glMaterialfv(GL_FRONT, GL_AMBIENT, convertidos.data());
    GLfloat brillo_gl = brillo;
    glMaterialfv(GL_FRONT, GL_SHININESS, &brillo_gl);
}

Material::Material()
    :Material(
        Tupla4f(1,1,1,1), Tupla4f(1,1,1,1), Tupla4f(1,1,1,1), 20
    ) 
    {}