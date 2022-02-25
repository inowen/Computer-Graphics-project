#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

/*
 * Clase abstracta. Las subclases definen posición/dirección en el constructor,
 * y se posicionan en el momento en el que se llame activar().
 */
class Luz {

protected:
    Tupla4f posicion; // Última componente es w=0 <=> direccional
    GLenum id; // GL_LIGHTi
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;

public:
    void activar();
    void desactivar();
};


#endif