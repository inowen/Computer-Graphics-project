#include "cubo_texturizado.h"


CuboTexturizado::CuboTexturizado(float lado) {
    float x = lado/2.0f;

    // Asignar vértices
    v.push_back(Tupla3f(-x,x,x)); // 0
    v.push_back(Tupla3f(x,x,x));
    v.push_back(Tupla3f(-x,-x,x));
    v.push_back(Tupla3f(x,-x,x));
    v.push_back(Tupla3f(-x,x,-x)); // 4
    v.push_back(Tupla3f(x,x,-x));
    v.push_back(Tupla3f(-x,-x,-x));
    v.push_back(Tupla3f(x,-x,-x));
    v.push_back(v[4]); // 8
    v.push_back(v[6]);
    v.push_back(v[5]);
    v.push_back(v[7]);
    v.push_back(v[4]); // 12
    v.push_back(v[6]);

    // Asignar caras
    // Frente
    f.push_back(Tupla3u(1,0,2));
    f.push_back(Tupla3u(1,2,3));
    // Arriba
    f.push_back(Tupla3u(4,0,1));
    f.push_back(Tupla3u(5,4,1));
    // Abajo
    f.push_back(Tupla3u(3,2,6));
    f.push_back(Tupla3u(7,3,6));
    // Izda
    f.push_back(Tupla3u(0,8,2));
    f.push_back(Tupla3u(2,8,9));
    // Dcha
    f.push_back(Tupla3u(10,1,3));
    f.push_back(Tupla3u(10,3,11));
    // Detrás
    f.push_back(Tupla3u(12,10,13));
    f.push_back(Tupla3u(13,10,11));


    // Asignar coordenadas de textura
    ct.push_back(Tupla2f(0.25f, 0.66f)); // 0
    ct.push_back(Tupla2f(0.5f, 0.66f));
    ct.push_back(Tupla2f(0.25f, 0.33f));
    ct.push_back(Tupla2f(0.5f, 0.33f));
    ct.push_back(Tupla2f(0.25f, 1)); // 4
    ct.push_back(Tupla2f(0.5f, 1));
    ct.push_back(Tupla2f(0.25f, 0));
    ct.push_back(Tupla2f(0.5f, 0));
    ct.push_back(Tupla2f(0, 0.66f)); // 8
    ct.push_back(Tupla2f(0, 0.33f));
    ct.push_back(Tupla2f(0.75f, 0.66f));
    ct.push_back(Tupla2f(0.75f, 0.33f));
    ct.push_back(Tupla2f(1, 0.66f)); // 12
    ct.push_back(Tupla2f(1, 0.33f));

}
