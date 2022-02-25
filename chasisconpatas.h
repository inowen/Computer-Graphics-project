#ifndef CCONPATAS_H_INCLUDED
#define CCONPATAS_H_INCLUDED

#include "materialregistry.h"
#include "aux.h"
#include "malla.h"
#include "chasis.h"
#include "patas.h"
#include "menus.h"


/**
 * Dimensiones iguales que las del cockpit,
 * solo que ahora tiene patas.
 */
class ChasisConPatas : public Malla3D {
    
    public:
    ChasisConPatas();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);
    void setColor(color c);
    void moverVentanas(float incremento);
    void moverPuertas(float incremento);

    private:
    Chasis chasis;
    Patas patas;
};

#endif