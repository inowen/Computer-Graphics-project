#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include "menus.h"
#include "materialregistry.h"
#include "cilindro.h"
#include "tetraedro.h"
#include "malla.h"
#include "esfera.h"

/**
 * Dimensiones: Es alrededor de 3.15m de larga. 
 * Posición: Empieza en el origen, se extiende en el eje positivo X
 */
class Cola : public Malla3D {

    public:
    Cola();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);
    void setColor(color c);

    private:
    Cilindro cilindro;
    Tetraedro tetraedro;
    Esfera esfera;

    void cilindroBase();
};

#endif