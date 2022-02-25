#ifndef CHASIS_H_INCLUDED
#define CHASIS_H_INCLUDED

#include "malla.h"
#include "menus.h"
#include "objply.h"
#include "puerta.h"
#include "materialregistry.h"

/**
 * Dimensiones: Alto: 2m, largo:3,9625m , ancho:2m
 * Posición: Centrado en el origen. Simétrico respecto del plano XY.
 * El eje Z pasa justamente por el centro de las puertas.
 */
class Chasis : public Malla3D {

    public:
    Chasis();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);
    void setColor(color c);
    void moverPuerta(float incremento);
    void moverVentana(float incremento);

    private:
    float proporcion_apertura_puerta = 0.0f;
    ObjPLY ply;
    Puerta puerta;
};

#endif