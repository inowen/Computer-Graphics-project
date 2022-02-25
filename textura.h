#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include <string>
#include <vector>
#include "jpg_imagen.h"
#include "aux.h"

class Textura {
    private:
    std::string nombre;
    GLuint textura_id = 0;
    unsigned char* data;
    int width, height;

    public:
    Textura(std::string archivo);
    ~Textura();
    void activar();
};

#endif