#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float len_lado_base, float altura)
{
   float x = len_lado_base / 2.0f;

   // inicializar la tabla de vértices
   v.push_back(Tupla3f(-x, 0.0f, x));
   v.push_back(Tupla3f(x, 0.0f, x));
   v.push_back(Tupla3f(-x, 0.0f, -x));
   v.push_back(Tupla3f(x, 0.0f, -x));
   v.push_back(Tupla3f(0.0f, altura, 0.0f));

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.push_back(Tupla3u(0,2,3));
   f.push_back(Tupla3u(1,0,3));
   f.push_back(Tupla3u(4,2,0));
   f.push_back(Tupla3u(4,1,3));
   f.push_back(Tupla3u(4,0,1));
   f.push_back(Tupla3u(4,3,2));
}


