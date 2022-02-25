#ifndef PUERTA_H_INCLUDED
#define PUERTA_H_INCLUDED

#include "aux.h"
#include "menus.h"
#include "malla.h"
#include "cubo.h"
#include "materialregistry.h"

/*
 * Dimensiones: Es 1.5 por 1.5, 
 * con la esquina inferior izquierda apoyada en (0,0). 
*/
class Puerta : public Malla3D {
    public:
    Puerta();
    void draw(modoDibujado modo_dibujado, bool modo_ajedrez);  // Override 
    void setColor(color c);
    /**
     * Permite aumentar la fracción de apertura de la ventana en @p incremento.
     * El valor total de apertura está en [0,1]
     */
    void moverVentana(float incremento);

    private:
    Cubo cubo;
    float proporcion_ventana_bajada = 0.0f;
};


#endif