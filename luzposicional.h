#ifndef LUZ_POSICIONAL_H_DEFINED
#define LUZ_POSICIONAL_H_DEFINED

#include "luz.h"

class LuzPosicional : public Luz {

    public:
        LuzPosicional(Tupla3f pos, GLenum luz, Tupla4f c_ambiente, Tupla4f c_especular, Tupla4f c_difuso);

};

#endif