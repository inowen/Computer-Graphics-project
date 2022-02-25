#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara {
    public:
    Camara(int tipo, Tupla3f eye, Tupla3f at, Tupla3f up, float left, 
        float right, float bottom, float top, float near, float far);
    // Examinar (lo que se ha seleccionado)
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);

    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);

    // Mover === Cambiar sus x,y,z? Pero eso en relación a qué?
    // En qué momento se posiciona la cámara? Se le aplican transforms
    // del ModelView? 
    void mover(float x, float y, float z);
    void zoom(float factor);
    void setObserver(); // gluLookAt
    void setProyeccion(); // Projection matrix 

    void setBottom(float val) {bottom=val;}
    void setTop(float val) {top=val;}
    void setLeft(float val) {left = val;}
    void setRight(float val) {right = val;}
    void setEye(Tupla3f newEye) {eye=newEye;}
    void setAt(Tupla3f newAt) {at=newAt;}
    void setObserverDistance(float val) {observer_distance = val;}

    void resetOrientation();

    private:
    Tupla3f eye, at, up;
    int tipo = 1; // Ortogonal o perspectiva, 0=ortogonal
    float left, right, near, far;
    float bottom, top;

    // Eye, at, up son los valores de los que se parte,
    // y estos ángulos y distancias representan un offset. 
    float observer_angle_x = 0, observer_angle_y = 0;
    float observer_distance = 10;
    float examinar_angle_x = 0, examinar_angle_y = 0;

};


#endif