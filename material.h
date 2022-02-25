#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED
#include "aux.h"


class Material {
    private:
        Tupla4f difuso, especular, ambiente;
        float brillo;

    public:
        Material();
        Material(
            Tupla4f mdifuso, 
            Tupla4f mespecular, 
            Tupla4f mambiente, 
            float brillo
        )
        : difuso(mdifuso), 
        especular(mespecular), 
        ambiente(mambiente), 
        brillo(brillo) {}

        void aplicar() const;
};
#endif