#ifndef ASPAS_H_INCLUDED
#define ASPAS_H_INCLUDED

#include "menus.h"
#include "materialregistry.h"
#include "malla.h"
#include "cilindro.h"
#include "cubo.h"

/**
 * Dimensiones: Radio de las aspas es un poco superior a 4.
 * Ubicación: Se encuentran sobre el plano XY,
 *              desplazados sobre el eje Z en <longitud_cilindro>
 */ 
class Aspas : public Malla3D {

    public:
    Aspas(int num_aspas);
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);
    void setColor(color c);


    private:
    Cilindro cilindro;
    Cubo cubo;
    const float longitud_cilindro = 0.6f;
    unsigned num_aspas = 6;
    const float longitud_aspas = 2;

    void aspa(modoDibujado modo_dibujado, bool modo_ajedrez);
};


#endif