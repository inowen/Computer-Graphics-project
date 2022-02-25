#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include <iostream>

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   float m = lado/2; // Medio lado
   v.push_back(Tupla3f(-m, -m, m));
   v.push_back(Tupla3f(m,-m,m)); // 1
   v.push_back(Tupla3f(-m,m,m));
   v.push_back(Tupla3f(m,m,m)); // 3
   v.push_back(Tupla3f(-m,m,-m));
   v.push_back(Tupla3f(m,m,-m));
   v.push_back(Tupla3f(m,-m,-m)); // 6
   v.push_back(Tupla3f(-m,-m,-m));

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   std::vector<Tupla3u> caras {
      Tupla3u(3,2,0),   Tupla3u(3,0,1), // front
      Tupla3u(4,5,6),   Tupla3u(6,7,4), // back PROBLEM: The second one. (now changed 6 for 7 and reversed)
      Tupla3u(4,2,3),   Tupla3u(4,3,5), // top
      Tupla3u(0,7,1),   Tupla3u(6,1,7), // bottom
      Tupla3u(2,4,0),   Tupla3u(0,4,7), // left
      Tupla3u(1,6,3),   Tupla3u(3,6,5)  // right
   };
   f.insert(f.end(), caras.begin(), caras.end());
}

