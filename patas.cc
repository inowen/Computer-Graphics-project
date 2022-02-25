#include "patas.h"

Patas::Patas() : cilindro(10, 10, 0.5f, 1, true, true) {
    cilindro.setMaterial(MaterialRegistry().bronze);
}


void Patas::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    glPushMatrix();
        glRotatef(ANG_ROT_PATAS, 1,0,0);
        pata(modo_dibujado, modo_ajedrez);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-ANG_ROT_PATAS, 1,0,0);
        pata(modo_dibujado, modo_ajedrez);
    glPopMatrix();
}

// Dibujar una pata (la mitad de las patas)
void Patas::pata(modoDibujado modo_dibujado, bool modo_ajedrez) {
    // "Suela" de la pata
    glPushMatrix();
        glTranslatef(0, -0.5f, 0); // Con radio 0.5, está 0.45 debajo del eje X
        glScalef(2, 0.1f, 0.1f);
        glTranslatef(-0.5f, 0,0);
        glRotatef(-90, 0,0,1);
        cilindro.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
    // Barra vertical derecha
    glPushMatrix();
        glTranslatef(0.5f, -0.5, 0);
        glScalef(0.1f, 0.5f, 0.1f);
        cilindro.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
    // Barra vertical izquierda
    glPushMatrix();
        glTranslatef(-0.5f, -0.5, 0);
        glScalef(0.1f, 0.5f, 0.1f);
        cilindro.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
}

void Patas::setColor(color c) {
    cilindro.setColor(c);
}