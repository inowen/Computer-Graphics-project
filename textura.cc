#include "textura.h"


Textura::Textura(std::string nombre) {
    this->nombre = nombre;
}


void Textura::activar() {
    if (this->textura_id == 0) {
        jpg::Imagen* pimg = nullptr;
        pimg = new jpg::Imagen(nombre);
        width = pimg->tamX();
        height = pimg->tamY();
        data = pimg->leerPixels();
        glGenTextures(1, &textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 
                GL_RGB, width, height, 
                GL_RGB, GL_UNSIGNED_BYTE, data
        );
    }
    glBindTexture(GL_TEXTURE_2D, textura_id);
}

Textura::~Textura() {
    delete [] data;
}