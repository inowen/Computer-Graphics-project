#include "math_helper.h"

Tupla3f MathHelper::multMatriz4f(float mat[16], Tupla3f vert)
{
    Tupla3f result;
    result(0) = mat[0]*vert(0) + mat[4]*vert(1) + mat[8]*vert(2) + mat[12];
    result(1) = mat[1]*vert(0) + mat[5]*vert(1) + mat[9]*vert(2) + mat[13];
    result(2) = mat[2]*vert(0) + mat[6]*vert(1) + mat[10]*vert(2) + mat[14];
    return result;
}