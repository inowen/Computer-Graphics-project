#ifndef MATH_HELPER_H_INCLUDED
#define MATH_HELPER_H_INCLUDED

#include "aux.h"
#include "tuplasg.h"

class MathHelper {
    public:
    /**
     * @brief Aplica una matriz de transformación 4D OpenGL 
     *        a un vértice.
     * @param mat La matriz 
     * @param vert El vértice
     * @return Tupla3f 
     */
    Tupla3f multMatriz4f(float mat[16], Tupla3f vert);

};

#endif