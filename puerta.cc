#include "puerta.h"

Puerta::Puerta() {
    cubo = Cubo(1.0f);
}

void Puerta::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {

    cubo.setMaterial(MaterialRegistry().red_rubber);
    glPushMatrix();
        glScalef(1,1,0.2f); // Hacer la puerta fina
        // La base de la puerta
        glPushMatrix();
            glTranslatef(0.75f, 0, 0);
            glScalef(1.5f, 0.5f, 1.0f); 
            glTranslatef(0.0f, 0.5f, 0.0f);
            cubo.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
        // Subir hacia encima de la base de la puerta (que tiene altura 0.5)
        glTranslatef(0.0f, 0.5f, 0.0f);
        // El marco de la puerta a la izquierda 
        glPushMatrix();
            glScalef(0.2f, 1, 1);
            glTranslatef(0.5f, 0.5f, 0);// Apoyar cubo en (0,0)
            cubo.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
        // El marco de la derecha de la puerta
        glPushMatrix();
            glTranslatef(1.3f, 0, 0);
            glScalef(0.2f, 1, 1);
            glTranslatef(0.5f, 0.5f, 0); // Apoyado en (0,0)
            cubo.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
        // El marco superior de la puerta
        glPushMatrix();
            glTranslatef(0.2f, 0.8f, 0);
            glScalef(1.1f, 0.2f, 1);
            glTranslatef(0.5f, 0.5f, 0); // Apoyado en (0,0)
            cubo.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();
        // La ventana
        float max_bajada = 0.45f;
        glPushMatrix();
            glTranslatef(0.2f, -max_bajada*proporcion_ventana_bajada, 0.1f);
            glScalef(1.1f, 0.8f, 0.1);
            glTranslatef(0.5f, 0.5f, 0); // Apoyado en (0,0)
            cubo.setMaterial(MaterialRegistry().negro_especular);
            cubo.draw(modo_dibujado, modo_ajedrez);
        glPopMatrix();

    glPopMatrix();

}


void Puerta::moverVentana(float incremento) {
    proporcion_ventana_bajada += incremento;
    if (proporcion_ventana_bajada > 1) {
        proporcion_ventana_bajada = 1;
    }
    else if (proporcion_ventana_bajada < 0) {
        proporcion_ventana_bajada = 0;
    }
}

void Puerta::setColor(color c) {
    cubo.setColor(c);
}