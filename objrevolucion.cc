#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "menus.h"
#include "rotaciones.h"
#include <algorithm>
#include <cmath>




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, eje eje_rotacion) {
   this->tapa_sup = tapa_sup;
   this->tapa_inf = tapa_inf;
   std::vector<Tupla3f> perfil;
   ply::read_vertices(archivo, perfil);
   tam_perfil = perfil.size();
   // Invertir los vértices del perfil si están al revés.
   bool al_reves = (eje_rotacion==EJE_X && perfil[0](0)>perfil[perfil.size()-1](0))
                     || (eje_rotacion==EJE_Y && perfil[0](1)>perfil[perfil.size()-1](1))
                     || (eje_rotacion==EJE_Z && perfil[0](2)>perfil[perfil.size()-1](2));
   if (al_reves) {
      std::reverse(perfil.begin(), perfil.end());
   }
   crearMalla(perfil, num_instancias, eje_rotacion, tapa_inf, tapa_sup);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, eje eje_rotacion) {
   this->tapa_sup = tapa_sup;
   this->tapa_inf = tapa_inf;
   tam_perfil = archivo.size();
   crearMalla(archivo, num_instancias, eje_rotacion, tapa_inf, tapa_sup);
}


void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,
   eje eje_rotacion, bool tapa_inf, bool tapa_sup) 
{
   this->tapa_inf = tapa_inf;
   this->tapa_sup = tapa_sup;

   // Polo Sur:
   Tupla3f candidato = perfil_original[0];
   if (es_polo(candidato, eje_rotacion)) {
      polo_sur = candidato;
      perfil_original.erase(perfil_original.begin());
   }
   else {
      polo_sur = hacer_polo(perfil_original[0], eje_rotacion);
   }
   
   // Polo Norte: 
   candidato = perfil_original[perfil_original.size()-1];
   if (es_polo(candidato, eje_rotacion)) {
      polo_norte = candidato;
      perfil_original.erase(--perfil_original.end());
   }
   else {
      polo_norte = hacer_polo(perfil_original[perfil_original.size()-1], eje_rotacion);
   }

   if (this->tapa_inf) {
      perfil_original.insert(perfil_original.begin(), polo_sur);
   }
   if (this->tapa_sup) {
      perfil_original.push_back(polo_norte);
   }

   tam_perfil = perfil_original.size();

   // Crear lista de vértices rotando el perfil original
   this->v.clear();
   for (int i=0; i<num_instancias+1; ++i) {
      for (int j=0; j<perfil_original.size(); ++j) {
         v.push_back(rotarPunto(2*PI*i / (float)num_instancias, eje_rotacion, perfil_original[j]));
      }
   }



   // Crear la lista de caras a partir de la lista de vértices del cuerpo
   for (int n_perfil=0; n_perfil<num_instancias; n_perfil++) {
      int ind_primer_punto = n_perfil*perfil_original.size();
      int inicio_siguiente_perfil = (n_perfil+1)*perfil_original.size();
      for (int n_pt=ind_primer_punto; n_pt<inicio_siguiente_perfil-1; ++n_pt) {
         int ind_izquierda = (n_pt+perfil_original.size()) % v.size(),
             ind_arriba = n_pt + 1, 
             ind_opuesta = ind_izquierda + 1;
         // Dibujar triángulos
         f.push_back(Tupla3u(ind_opuesta, ind_izquierda, n_pt));
         f.push_back(Tupla3u(ind_opuesta, n_pt, ind_arriba));
      }
   }

}


/*
 * Si el punto en cuestión es un polo si se rota sobre el eje dado
 */
bool ObjRevolucion::es_polo(Tupla3f candidato, eje axis) {
   bool ret = false;
   switch (axis) {
      case EJE_X:
         ret = (candidato(1)==0 && candidato(2)==0);
         break;
      case EJE_Y:
         ret = (candidato(0)==0 && candidato(2)==0);
         break;
      case EJE_Z:
         ret = (candidato(0)==0 && candidato(1)==0);
         break;
   } 
   return ret;
}

Tupla3f ObjRevolucion::hacer_polo(Tupla3f src, eje eje_rotacion) {
   if (eje_rotacion == EJE_X) {
      return Tupla3f(src(0), 0, 0);
   }
   else if (eje_rotacion == EJE_Y) {
      return Tupla3f(0, src(1), 0);
   }
   else {
      return Tupla3f(0, 0, src(2));
   }
}


void ObjRevolucion::calcularCoordTextura() {
   ct.clear();

   // Distancia total de principio a fin del perfil
   float distancia_total = 0.0f;
   for (int i=1; i<tam_perfil; ++i) {
      Tupla3f vec_dist = v[i]-v[i-1]; 
      distancia_total += sqrt(vec_dist.lengthSq());
   }

   // CUERPO
   for (int i=0; i<v.size(); ++i) {
      Tupla3f c_actual = v[i];
      float s,t;
      int num_perfil_estoy = i / tam_perfil; // Empieza numerando en 0
      int num_perfiles_total = v.size() / tam_perfil;
      s = ((float)num_perfil_estoy) / num_perfiles_total-1;

      // t se obtiene calculando la distancia desde el inicio del perfil
      int pos_inicio_perfil = i - (i%tam_perfil);
      int num_avanzar = i%tam_perfil;

      float altura_c_actual = 0;
      for (int p=1; p<=num_avanzar; ++p) {
         int ind_anterior = pos_inicio_perfil+p-1;
         int ind_actual = pos_inicio_perfil+p;
         Tupla3f vec_dist = v[ind_actual]-v[ind_anterior];
         altura_c_actual += sqrt(vec_dist.lengthSq());
      }
      t = altura_c_actual / distancia_total;

      ct.push_back(Tupla2f(s,t));
   }

}