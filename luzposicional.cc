#include "luzposicional.h"

LuzPosicional::LuzPosicional(
    Tupla3f pos, GLenum luz, Tupla4f c_ambiente, Tupla4f c_especular, Tupla4f c_difuso
)
{ 
    Tupla4f pos4f(pos(0), pos(1), pos(2), 1);
    posicion = pos4f;
    id = luz;
    colorAmbiente = c_ambiente;
    colorEspecular = c_especular;
    colorDifuso = c_difuso;
}