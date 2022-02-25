#ifndef LUZ_DIRECCIONAL_H_INCLUDED
#define LUZ_DIRECCIONAL_H_INCLUDED

#include "luz.h"
#include "rotaciones.h"

class LuzDireccional : public Luz {

public:
    LuzDireccional (
        Tupla2f direccion, GLenum id_luz, Tupla4f c_ambiente, Tupla4f c_especular, Tupla4f c_difuso
    );

protected:
    float alpha, beta; // Son en grados sexagesimales

public:
    void activar();
    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);

};

#endif