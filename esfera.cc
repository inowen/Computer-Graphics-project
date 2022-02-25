#include "esfera.h"

Esfera::Esfera(int num_vert_perfil, int num_instancias_perf, float r, bool tapa_sup, bool tapa_inf)
: radio(r) 
{
    // Crear el perfil de la esfera (semicírculo: PI radianes)
    std::vector<Tupla3f> perfil;
    float inc_angle = PI / num_vert_perfil;
    for (float total_ang=-PI/2.0f+inc_angle; total_ang<PI/2.0f; total_ang+=inc_angle) {
        perfil.push_back(Tupla3f(cos(total_ang), sin(total_ang), 0.0f));
    }

    // Crear la malla
    crearMalla(perfil, num_instancias_perf, EJE_Y, tapa_inf, tapa_sup);
}
