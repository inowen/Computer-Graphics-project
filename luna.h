#ifndef LUNA_H_INClUDED
#define LUNA_H_INClUDED

#include <vector>
#include "esfera.h"
#include "textura.h"
#include "aux.h"
#include "luzposicional.h"
#include "menus.h"
#include "materialregistry.h"

/**
 * Posición inicial: El origen.
 * Es una luz con una esfera alrededor que visualiza
 * la posición de la luz.
 */
class Luna {
    public:
    Luna(GLenum id_luz);
    ~Luna();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez, bool iluminar);
    void setColor(color);

    private:
    Esfera* esfera = nullptr;
    LuzPosicional* luz = nullptr;
};


#endif
