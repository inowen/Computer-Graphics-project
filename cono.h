#ifndef CONO_H_DEFINIDO
#define CONO_H_DEFINIDO

#include "objrevolucion.h"

class Cono : public ObjRevolucion 
{
    public:
        Cono(int num_vert_perfil=2, int num_instancias_perf=20, float h=1.0f, float r=1.0f, bool tapa_sup=true, bool tapa_inf=true);

    private:
        float altura = 1, radio = 1;
};


#endif