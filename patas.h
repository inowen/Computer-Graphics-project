#ifndef PATAS_H_INCLUDED
#define PATAS_H_INCLUDED

#include "menus.h"
#include "malla.h"
#include "aux.h"
#include "cilindro.h"
#include "materialregistry.h"

/**
 * Posición: Paralelas al eje X, debajo del eje X.
 * Dimensiones: Entre las dos patas hay 1m. La "suela" mide 2m.
 */
class Patas : public Malla3D {

    public:
    Patas();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);
    void setColor(color c);

    private:
    const float ANG_ROT_PATAS = 35;
    Cilindro cilindro; // h=1, r=0.5
    void pata(modoDibujado modo_dibujado, bool modo_ajedrez);
};


#endif