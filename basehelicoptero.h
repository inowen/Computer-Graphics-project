#ifndef BASE_HELICOPTERO_H_INCLUDED
#define BASE_HELICOPTERO_H_INCLUDED

#include "menus.h"
#include "materialregistry.h"
#include "malla.h"
#include "colaconaspas.h"
#include "chasisconpatas.h"

class BaseHelicoptero : public Malla3D {

    public:
    BaseHelicoptero();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);
    void setColor(color c);
    void moverVentanas(float incremento);
    void moverPuertas(float incremento);
    void moverAspas(float incremento);

    private:
    ColaConAspas cola;
    ChasisConPatas chasis;

};


#endif