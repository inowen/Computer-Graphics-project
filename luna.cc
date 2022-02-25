#include "luna.h"

Luna::Luna(GLenum id_luz) {
    // Crear la esfera
    esfera = new Esfera(10, 20, 1, true, true);

    // Texturizar la esfera
    Textura* tex = new Textura("luna.jpg");
    esfera->setTextura(tex);
    esfera->calcularCoordTextura();

    // Crear la luz
    Tupla4f ambiente(0.8f,0.8f,0.8f,1);
    Tupla4f especular(0.8f,0.8f,0.8f,1);
    Tupla4f difusa(0.8f,0.8f,0.8f,1);
    luz = new LuzPosicional(Tupla3f(0,0,0), id_luz, ambiente, especular, difusa);
}



void Luna::draw(modoDibujado modo_dibujado, bool modo_ajedrez, bool iluminar) {
    esfera->draw(modo_dibujado, modo_ajedrez);
    if (iluminar) {
        luz->activar();
    }
    else luz->desactivar();
}



void Luna::setColor(color c) {
    esfera->setColor(c);
}


Luna::~Luna() {
    delete esfera;
    delete luz;
}