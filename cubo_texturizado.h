#ifndef CUBO_TEX_H_INCLUDED
#define CUBO_TEX_H_INCLUDED

#include "aux.h"
#include "materialregistry.h"
#include "malla.h"

class CuboTexturizado : public Malla3D {
    public:
    // Constructor asigna vértices(v), caras(f), y coordenadas de textura (ct)
    CuboTexturizado(float lado);
};


#endif