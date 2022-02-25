#include "cono.h"

Cono::Cono(int num_vert_perfil, int num_instancias_perf, float h, float r, bool tapa_sup, bool tapa_inf)
    : altura(h), radio(r)
{
    // Generar perfil, luego llamada a crearMalla
    std::vector<Tupla3f> perfil;
    // Crear vértices en un bucle, crear num_vert_perfil vértices.
    Tupla3f inicio(r, 0.0f, 0.0f);
    Tupla3f fin(0.0f, h, 0.0f);
    Tupla3f vector_dif = fin - inicio;
    Tupla3f vect_desplazamiento = vector_dif / (float)num_vert_perfil;
    for (int i=0; i<num_vert_perfil; ++i) {
        perfil.push_back(inicio + ((float)i)*vect_desplazamiento);
    }

    // Crear malla
    this->crearMalla(perfil, num_instancias_perf, EJE_Y, tapa_inf, tapa_sup);
}
