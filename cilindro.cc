#include "cilindro.h"

Cilindro::Cilindro(int num_vert_perfil, int num_instancias_perf, float r, float h, bool tapa_sup, bool tapa_inf)
: altura(h), radio(r)
{
    // Generar el perfil
    Tupla3f abajo_lado(r, 0.0f, 0.0f);
    Tupla3f arriba_lado(r, h, 0.0f);
    Tupla3f vect_lado = arriba_lado - abajo_lado; // Va de abajo hasta arriba
    Tupla3f vect_desplazamiento = vect_lado / ((float)num_vert_perfil);
    std::vector<Tupla3f> perfil;
    for (int i=0; i<num_vert_perfil; ++i) {
        perfil.push_back(abajo_lado + (float(i))*vect_desplazamiento);
    }

    // Crear la malla
    this->crearMalla(perfil, num_instancias_perf, EJE_Y, tapa_inf, tapa_sup);
}