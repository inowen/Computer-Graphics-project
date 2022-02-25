#include "cola.h"

Cola::Cola()
: cilindro(10,10,0.5f, 1, true,true),
  esfera(10, 10, 0.5f, true, true), 
  tetraedro(1, 1) 
{
    cilindro.setMaterial(MaterialRegistry().polished_gold);
    esfera.setMaterial(MaterialRegistry().polished_gold);
    tetraedro.setMaterial(MaterialRegistry().red_rubber);
}

void Cola::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    glPushMatrix();
        // Primer cilindro
        glPushMatrix();
            glScalef(1.1f, 0.6f, 0.6f);
            glRotatef(-90, 0,0,1);
            cilindro.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
        glTranslatef(1, 0, 0);
        // Segundo cilindro
        glPushMatrix();
            glScalef(1.1f, 0.5f, 0.5f);
            glRotatef(-90, 0,0,1);
            cilindro.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
        glTranslatef(1,0,0);
        // Tercer cilindro
        glPushMatrix();
            glScalef(1.1f, 0.4f, 0.4f);
            glRotatef(-90, 0,0,1);
            cilindro.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
        glTranslatef(1,0,0);
        // esfera y tetraedro
        glPushMatrix();
            glScalef(0.3f, 0.3f, 0.3f);
            esfera.draw(modo_dibujado, modo_ajedrez);
            glTranslatef(0, 0.9f, 0);
            tetraedro.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
    glPopMatrix();
}


void Cola::setColor(color c) {
    cilindro.setColor(c);
    esfera.setColor(c);
    tetraedro.setColor(c);
}