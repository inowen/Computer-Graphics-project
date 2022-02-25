#include "basehelicoptero.h"

BaseHelicoptero::BaseHelicoptero() { }


void BaseHelicoptero::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    glPushMatrix();
        chasis.draw(modo_dibujado, modo_ajedrez);
        glTranslatef(1.98125f, 0, 0);
        cola.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
}

void BaseHelicoptero::moverVentanas(float incremento) {
    chasis.moverVentanas(incremento);
}
void BaseHelicoptero::moverPuertas(float incremento) {
    chasis.moverPuertas(incremento);
}

void BaseHelicoptero::moverAspas(float incremento) {
    cola.moverAspas(incremento);
}

void BaseHelicoptero::setColor(color c) {
    cola.setColor(c);
    chasis.setColor(c);
}