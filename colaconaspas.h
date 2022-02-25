#ifndef COLACONASPAS_H_INCLUDED
#define COLACONASPAS_H_INCLUDED

#include "menus.h"
#include "materialregistry.h"
#include "malla.h"
#include "cola.h"
#include "aspas.h"

class ColaConAspas : public Malla3D {

    public:
    ColaConAspas();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);
    void setColor(color c);
    void moverAspas(float incremento);

    private:
    float angulo_giro_aspas = 0;
    Aspas aspas;
    Cola cola;
};


#endif