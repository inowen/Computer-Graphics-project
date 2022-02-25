#include "luzdireccional.h"

LuzDireccional::LuzDireccional (
    Tupla2f direccion, GLenum id_luz, Tupla4f c_ambiente, Tupla4f c_especular, Tupla4f c_difuso
)
: alpha(direccion[0]), beta(direccion[1])
{
    this->id = id_luz;
    this->colorAmbiente = c_ambiente;
    this->colorEspecular = c_especular;
    this->colorDifuso = c_difuso;
}

void LuzDireccional::activar() {
    // Asignar la nueva posición 
    const float PI = 3.14159f;
    float alpha_radians = alpha*PI/180.0f,
          beta_radians  = beta*PI/180.0f;
    this->posicion = -Tupla4f(cos(alpha_radians), sin(beta_radians), sin(alpha_radians), 0);

    Luz::activar();
}


void LuzDireccional::variarAnguloAlpha(float inc) {
    this->alpha += inc;
}

void LuzDireccional::variarAnguloBeta(float inc) {
    this->beta += inc;
}