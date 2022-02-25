#ifndef CILINDRO_H_DEFINED
#define CILINDRO_H_DEFINED

#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
    public:
        Cilindro(int num_vert_perfil=2, int num_instancias_perf=20, float r=1.0f, float h=1.0f, bool tapa_sup=true, bool tapa_inf=true);
    
    private:
        float altura, radio;
};


#endif