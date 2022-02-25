#include "helicoptero.h"

Helicoptero::Helicoptero() : aspas(16) { }

void Helicoptero::moverAspas(float incremento) {
    base.moverAspas(incremento);
    moverAspasSuperiores(incremento);
}

void Helicoptero::moverPuertas(float incremento) {
    base.moverPuertas(incremento);
}


void Helicoptero::moverVentanas(float incremento) {
    base.moverVentanas(incremento);
}


void Helicoptero::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    // Posicionar la base
    base.draw(modo_dibujado, modo_ajedrez);
    // Las aspas
    glPushMatrix();
        glTranslatef(0, 1.3f, 0);
        glScalef(2, 1, 2);
        glRotatef(-90, 1,0,0);
        glRotatef(ang_aspas_superiores, 0,0,1);
        aspas.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
}


void Helicoptero::moverAspasSuperiores(float incremento) {
    ang_aspas_superiores += incremento;
}


void Helicoptero::tickAnimacion(
    float multiplicador_velocidad,
    float multiplicador_velocidad_aspas,
    float multiplicador_velocidad_puertas,
    float multiplicador_velocidad_ventanas
) 
{
    float incremento_animacion = 0.01f*multiplicador_velocidad;
    switch (estado_animacion) {
        case ABRIENDO_PUERTAS:
            incremento_animacion *= multiplicador_velocidad_puertas;
            this->moverPuertas(incremento_animacion);
            progreso_animacion_actual += incremento_animacion;
            if (progreso_animacion_actual >= 1) {
                estado_animacion = ABRIENDO_VENTANAS;
                progreso_animacion_actual = 0;
            }
            break;
        case ABRIENDO_VENTANAS:
            incremento_animacion *= multiplicador_velocidad_ventanas;
            this->moverVentanas(incremento_animacion);
            progreso_animacion_actual += incremento_animacion;
            if (progreso_animacion_actual >= 1) {
                estado_animacion = CERRANDO_PUERTAS;
                progreso_animacion_actual = 0;
            }
            break;
        case CERRANDO_PUERTAS:
            incremento_animacion *= multiplicador_velocidad_puertas;
            this->moverPuertas(-incremento_animacion);
            progreso_animacion_actual += incremento_animacion;
            if (progreso_animacion_actual >= 1) {
                estado_animacion = CERRANDO_VENTANAS;
                progreso_animacion_actual = 0;
            }
            break;
        case CERRANDO_VENTANAS:
            incremento_animacion *= multiplicador_velocidad_ventanas;
            this->moverVentanas(-incremento_animacion);
            progreso_animacion_actual += incremento_animacion;
            if (progreso_animacion_actual >= 1) {
                estado_animacion = MOVIENDO_ASPAS;
                progreso_animacion_actual = 0;
            }
            break;
        case MOVIENDO_ASPAS:
            incremento_animacion *= multiplicador_velocidad_aspas;
            this->moverAspas(360*incremento_animacion);
            progreso_animacion_actual += incremento_animacion;
            if (progreso_animacion_actual >= 1) {
                estado_animacion = ABRIENDO_PUERTAS;
                progreso_animacion_actual = 0;
            }
            break;
    }

}

void Helicoptero::setColor(color c) {
    base.setColor(c);
    aspas.setColor(c);
}