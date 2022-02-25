#include "chasis.h"

Chasis::Chasis(): ply("plys/heli_esqueleto_cockpit.ply") {
    ply.setMaterial(MaterialRegistry().chassis_black);
    puerta = Puerta();
}

void Chasis::draw(modoDibujado modo_dibujado, bool modo_ajedrez) {
    // Rotar el ply para que la entrada esté por los lados
    glPushMatrix();
        glRotatef(90, 1,0,0);
        ply.draw(modo_dibujado, modo_ajedrez);
    glPopMatrix();
    // Dibujar la puerta en Z positivo
    glPushMatrix();
    {
        glTranslatef(-0.422181f, -0.332094f, 1);
        glScalef(0.562908f, 0.442792f, 1);
        float max_rotado_puerta = 65.0f;
        float rotado_puerta = -max_rotado_puerta*proporcion_apertura_puerta;
        glRotatef(rotado_puerta, 0,1,0);
        puerta.draw(modo_dibujado, modo_ajedrez);
    }
    glPopMatrix();
    // Dibujar la puerta en el lado con Z negativo
    glPushMatrix();
    {
        glScalef(1, 1, -1); // Invertir
        glTranslatef(-0.422181f, -0.332094f, 1);
        glScalef(0.562908f, 0.442792f, 1);
        float max_rotado_puerta = 65.0f;
        float rotado_puerta = -max_rotado_puerta*proporcion_apertura_puerta;
        glRotatef(rotado_puerta, 0,1,0);
        puerta.draw(modo_dibujado, modo_ajedrez);
    }
    glPopMatrix();
}

void Chasis::moverVentana(float incremento) {
    puerta.moverVentana(incremento);
}

void Chasis::moverPuerta(float incremento) {
    proporcion_apertura_puerta += incremento;
    if (proporcion_apertura_puerta > 1) {
        proporcion_apertura_puerta = 1;
    }
    else if (proporcion_apertura_puerta < 0) {
        proporcion_apertura_puerta = 0;
    }
}

void Chasis::setColor(color c) {
    ply.setColor(c);
    puerta.setColor(c);
}