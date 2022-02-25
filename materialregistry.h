#ifndef MATERIAL_REGISTRY_INCLUDED
#define MATERIAL_REGISTRY_INCLUDED
#include "aux.h"
#include "tuplasg.h"
#include "material.h"

class MaterialRegistry {
public:
    const Material blanco_difuso = Material
    (
        Tupla4f(0.8f, 0.8f, 0.8f, 0.8f),
        Tupla4f(0,0,0,0),
        Tupla4f(0.1,0.1,0.1,1.0),
        0
    );

    const Material negro_especular = Material
    (
        Tupla4f(0.1f, 0.1f, 0.1f, 1.0f), // Difuso
        Tupla4f(0.8f, 0.8f, 0.8f, 1.0f), // Especular
        Tupla4f(0.0f, 0.0f, 0.0f, 1.0f), // Ambiente
        50
    );

    const Material chassis_black = Material
    (
        Tupla4f(0.25f, 0.25f, 0.25f, 1.0f), // Difuso
        Tupla4f(0.4f, 0.4f, 0.4f, 1.0f), // Especular
        Tupla4f(0.1f, 0.1f, 0.1f, 1.0f), // Ambiente
        9
    );

    const Material especular_tierra = Material 
    (
        Tupla4f(0.8f, 0.8f, 0.8f, 1.0f),
        Tupla4f(0.9f, 0.9f, 0.9f, 1.0f),
        Tupla4f(0.4f, 0.4f, 0.4f, 1.0f),
        20
    );

    const Material rojo_puro = Material
    (
        Tupla4f(1,0,0,1),
        Tupla4f(1,0,0,1),
        Tupla4f(1,0,0,1),
        0
    );
    const Material verde_puro = Material
    (
        Tupla4f(0,1,0,1),
        Tupla4f(0,1,0,1),
        Tupla4f(0,1,0,1),
        0
    );
    const Material azul_puro = Material
    (
        Tupla4f(0,0,1,1),
        Tupla4f(0,0,1,1),
        Tupla4f(0,0,1,1),
        0
    );
    const Material emerald = Material
    (
        Tupla4f(0.07568f, 0.61424f, 0.07568f, 1.0f), // Difuso
        Tupla4f(0.633f, 0.727811f, 0.633f, 1.0f), // Especular
        Tupla4f(0.0215f, 0.1745f, 0.0215f, 1.0f), // Ambiente
        0.6f * 128.0f
    );
    const Material jade = Material
    (
        Tupla4f(0.54f, 0.89f, 0.63f, 1.0f),
        Tupla4f(0.316228f, 0.316228f, 0.316228f, 1.0f),
        Tupla4f(0.135f, 0.2225f, 0.1575f, 1.0f),
        0.1f * 128.0f
    );
    const Material bronze = Material 
    (
        Tupla4f(0.714f, 0.4284f, 0.18144f, 1.0f),
        Tupla4f(0.393548f, 0.271906f, 0.166721f, 1.0f),
        Tupla4f(0.2125f, 0.1275f, 0.054f, 1.0f),
        0.2f * 128.0f

    );
    const Material chrome = Material
    (
        Tupla4f(0.4f, 0.4f, 0.4f, 1.0f), // Difuso
        Tupla4f(0.774598f, 0.774597f, 0.774597f, 1.0f), // Especular
        Tupla4f(0.25f, 0.25f, 0.25f, 1.0f), // Ambiente
        76.8f
    );
    const Material polished_gold = Material 
    (
        Tupla4f(0.34615f, 0.3143f, 0.0903f, 1.0f),
        Tupla4f(0.797357f, 0.723991f, 0.208006f, 1.0f),
        Tupla4f(0.24725f, 0.2245f, 0.0645f, 1.0f),
        83.2f
    );
    const Material red_rubber = Material
    (
        Tupla4f(0.5f,0.4f,0.4f,1.0f),
        Tupla4f(0.7f,0.04f,0.04f,1.0f),
        Tupla4f(0.05f,0.0f,0.0f,1.0f),
        10.0f
    );
    const Material yellow_rubber = Material
    (
        Tupla4f(0.5f,0.5f,0.4f,1.0f),
        Tupla4f(0.7f,0.7f,0.04f,1.0f),
        Tupla4f(0.05f,0.05f,0.0f,1.0f),
        10.f
    );
    const Material green_rubber = Material
    (
        Tupla4f(0.4f,0.5f,0.4f,1.0f),
        Tupla4f(0.04f,0.7f,0.04f,1.0f),
        Tupla4f(0.0f,0.05f,0.0f,1.0f),
        10.0f
    );
    const Material luna_emisivo = Material 
    (
        Tupla4f(0.8, 0.8, 0.8, 1),
        Tupla4f(0.8, 0.8, 0.8, 1),
        Tupla4f(0.8, 0.8, 0.8, 1),
        100.0f
    );
};


#endif