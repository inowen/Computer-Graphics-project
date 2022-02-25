#include "aspas.h"

Aspas::Aspas(int num_aspas)
: cilindro(10, 10, 0.5f, 1, true, true),
  cubo(1.0f)
{
    cubo.setMaterial(MaterialRegistry().jade);
    cilindro.setMaterial(MaterialRegistry().negro_especular);
    this->num_aspas = num_aspas;
}

void Aspas::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    // El cilindro
    float longitud_cilindro = 0.3f;
    glPushMatrix();
        glTranslatef(0, 0, -longitud_cilindro);
        glScalef(0.2f, 0.2f, longitud_cilindro);
        glRotatef(90, 1,0,0);
        cilindro.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();

    // Generar aspas variando el ángulo.
    glPushMatrix();
        float angle_increment = 360.0f/num_aspas;
        for (int i=0; i<num_aspas; ++i) {
            glRotatef(angle_increment, 0,0,1);
            aspa(modo_dibujado, modo_ajedrez);
        }
    glPopMatrix();
}

void Aspas::aspa(modoDibujado modo_dibujado, bool modo_ajedrez) {
    glPushMatrix();
        glRotatef(-45, 1,0,0); // Para girar levemente
        glTranslatef(0.1f, 0, 0);
        glScalef(longitud_aspas, 0.1f, 0.1f);
        glTranslatef(0.5f, 0, 0);
        cubo.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
}

void Aspas::setColor(color c) {
    cilindro.setColor(c);
    cubo.setColor(c);
}