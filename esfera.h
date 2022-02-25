#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "objrevolucion.h"

class Esfera : public ObjRevolucion {
    public:
        Esfera(int num_vert_perfil=10, int num_instancias_perf=20, float r=1.0f, bool tapa_sup=true, bool tapa_inf=true);
    
    private:
        const float PI = 3.14159265358979f;
        float radio;

};


#endif