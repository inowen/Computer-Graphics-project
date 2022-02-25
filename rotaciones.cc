#include "rotaciones.h"

// Crear una matriz de floats de rotación alpha grados sobre un eje dado
// Radianes!
Tupla3f rotarPunto(float angle, eje eje_rotacion, Tupla3f punto_rotar) {
   Tupla3f resultado = Tupla3f(0.0f, 0.0f, 0.0f);
   // Crear la matriz, en base al eje y al ángulo
   float matriz[3][3];
   if (eje_rotacion == EJE_X) {
      matriz[0][0]=1; matriz[0][1]=0; matriz[0][2]=0;
      matriz[1][0]=0; matriz[1][1]=cos(angle); matriz[1][2]=sin(angle);
      matriz[2][0]=0; matriz[2][1]=-sin(angle); matriz[2][2]=cos(angle);  
   }
   else if (eje_rotacion == EJE_Y) {
      matriz[0][0]=cos(angle); matriz[0][1]=0; matriz[0][2]=-sin(angle);
      matriz[1][0]=0; matriz[1][1]=1; matriz[1][2]=0;
      matriz[2][0]=sin(angle); matriz[2][1]=0; matriz[2][2]=cos(angle);
   }
   else {
      matriz[0][0]=cos(angle); matriz[0][1]=sin(angle); matriz[0][2]=0;
      matriz[1][0]=-sin(angle); matriz[1][1]=cos(angle); matriz[1][2]=0;
      matriz[2][0]=0; matriz[2][1]=0; matriz[2][2]=1;
   }

   // Multiplicar por la matriz
   for (int f_i=0; f_i<3; ++f_i) {
      for (int c_i=0; c_i<3; ++c_i) {
         resultado(f_i) += matriz[f_i][c_i] * punto_rotar(c_i);
      }
   }
   return resultado;
}