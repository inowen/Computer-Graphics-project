#include "chasisconpatas.h"

ChasisConPatas::ChasisConPatas() {}


void ChasisConPatas::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    chasis.draw(modo_dibujado, modo_ajedrez);
    // Patas
    glPushMatrix();
        glTranslatef(0, -0.9, 0);
        glScalef(2, 1, 1.5f);
        patas.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
}




void ChasisConPatas::moverPuertas(float incremento) {
    chasis.moverPuerta(incremento);
}
void ChasisConPatas::moverVentanas(float incremento) {
    chasis.moverVentana(incremento);
}

void ChasisConPatas::setColor(color c) {
    chasis.setColor(c);
    patas.setColor(c);
}