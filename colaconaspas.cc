#include "colaconaspas.h"

ColaConAspas::ColaConAspas() : aspas(8) {
}

void ColaConAspas::moverAspas(float incremento) {
    angulo_giro_aspas += incremento;
}

void ColaConAspas::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    // Cola 
    cola.draw(modo_dibujado, modo_ajedrez);

    // Posicionar las aspas detrás, giradas en el ángulo dado
    glPushMatrix();
        glTranslatef(3,0,0.4f);
        glScalef(0.4f, 0.4f, 1);
        glRotatef(angulo_giro_aspas, 0,0,1);
        aspas.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
}


void ColaConAspas::setColor(color c) {
    aspas.setColor(c);
    cola.setColor(c);
}