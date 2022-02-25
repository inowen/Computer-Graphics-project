#ifndef HELICOPTERO_H_INCLUDED
#define HELICOPTERO_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "menus.h"
#include "basehelicoptero.h"
#include "aspas.h"

class Helicoptero {
    public:
        Helicoptero();
        void draw(modoDibujado modo, bool ajedrez);
        void setColor(color c);
        void moverVentanas(float incremento);
        void moverPuertas(float incremento);
        void moverAspas(float incremento);
        void tickAnimacion(
            float multiplicador_velocidad_general,
            float multiplicador_velocidad_aspas,
            float multiplicador_velocidad_puertas,
            float multiplicador_velocidad_ventanas
        );
    
    private:
        float ang_aspas_superiores = 0;
        void moverAspasSuperiores(float incremento);
        estadoAnimacion estado_animacion = ABRIENDO_PUERTAS;
        float progreso_animacion_actual = 0.0f; // Es una proporción, en [0,1]

        BaseHelicoptero base;
        Aspas aspas;
};


#endif