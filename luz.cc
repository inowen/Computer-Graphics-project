#include "luz.h"


// Activa y posiciona la luz.
void Luz::activar() {
    glEnable(id);
    // Poner las 3 componentes
    glLightfv(id, GL_SPECULAR, (GLfloat*)((void*)&colorEspecular));
    glLightfv(id, GL_AMBIENT, (GLfloat*)((void*)&colorAmbiente));
    glLightfv(id, GL_DIFFUSE, (GLfloat*)((void*)&colorDifuso));
    // Posicionar
    glLightfv(id, GL_POSITION, (GLfloat*)((void*)&posicion));
}

void Luz::desactivar() {
    glDisable(id);
}