#ifndef MENUS_H
#define MENUS_H

#include "tuplasg.h"

typedef enum {
    NADA, 
    SELVISUALIZACION, 
    SELDIBUJADO, 
    ANIM_AUTOMATICA, 
    ANIM_MANUAL, 
    ILUMINACION, 
    SELECCIONAR_CAMARA
} menu;

typedef enum {PUNTO, LINEA, SOLIDO, AJEDREZ} modoVisualizacion;
typedef enum {INMEDIATO, DIFERIDO} modoDibujado;
typedef enum {EJE_X, EJE_Y, EJE_Z} eje;
typedef enum {SI, NO} si_o_no;
// Los colores tierra, helicóptero, etc son los que se usan para 
// la función de dibujado para la selección.
typedef enum {ROJO, VERDE, AZUL, TIERRA, HELICOPTERO, MONALISA, LUNA} color;
typedef enum {VENTANAS, PUERTAS, ASPAS, NINGUNO} itemAnimable;
enum estadoAnimacion {
    ABRIENDO_PUERTAS, 
    ABRIENDO_VENTANAS, 
    CERRANDO_PUERTAS, 
    CERRANDO_VENTANAS,
    MOVIENDO_ASPAS
};

enum MouseStatus {RIGHT_DOWN, LEFT_DOWN, NONE};
enum ObjetoEscena {_HELICOPTERO, _MONALISA, _TIERRA, _LUNA, _BACKGROUND};

class colores_seleccion {
    public:
    const Tupla3ub tierra;
    const Tupla3ub helicoptero;
    const Tupla3ub monalisa;
    const Tupla3ub luna;

    colores_seleccion(): 
        tierra(200,0,0), 
        helicoptero(0,200,0), 
        monalisa(0,0,200), 
        luna(150,150,0) {}
};
#endif