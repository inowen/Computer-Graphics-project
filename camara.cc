#include "camara.h"
#include "math_helper.h"

Camara::Camara(int tipo, Tupla3f eye, Tupla3f at, Tupla3f up, float left, 
    float right, float bottom, float top, float near, float far):
        tipo(tipo), eye(eye), at(at), up(up),
        left(left), right(right), bottom(bottom), top(top),
        near(near), far(far) 
{
    observer_angle_x = observer_angle_y = 0.0f;
    observer_distance = 10.0f;
}


// Configurar la matriz de proyección 
// Para mapear vértices 3D a puntos 2D de la imagen.
void Camara::setProyeccion() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (this->tipo) {
        // Perspectiva
        glFrustum( left, right, bottom, top, near, far );
    }
    else {
        // Ortogonal
        glOrtho(left, right, bottom, top, near, far);
    }
}


void Camara::setObserver() {
    glMatrixMode(GL_MODELVIEW);
    glRotatef(observer_angle_y, 0,1,0);
    glRotatef(observer_angle_x, 1,0,0);
    Tupla3f dir = eye - at;
    Tupla3f desplazamiento = dir.normalized() * observer_distance;
    Tupla3f zoomedEye = eye + desplazamiento;
    // En modo examinar, el eye rota alrededor del at
    // Obtener una matriz que tenga ese efecto
    GLfloat mat[16];
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(at(0), at(1), at(2));
        glRotatef(examinar_angle_y, 0,1,0);
        glRotatef(examinar_angle_x, 1,0,0);
        glTranslatef(-at(0), -at(1), -at(2));
        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    glPopMatrix();
    // Rotar el eye alrededor del at con la matriz
    Tupla3f rotatedEye = MathHelper().multMatriz4f(mat, zoomedEye);
    gluLookAt(
        rotatedEye(0), rotatedEye(1), rotatedEye(2),
        at(0), at(1), at(2),
        up(0), up(1), up(2)
    );
}


void Camara::zoom(float factor) {
    observer_distance += factor;
}

void Camara::rotarXFirstPerson(float angle) {
    observer_angle_x += angle;
}

void Camara::rotarYFirstPerson(float angle) {
    observer_angle_y += angle;
}


void Camara::rotarXExaminar(float angle) {
    examinar_angle_x += angle;
}

void Camara::rotarYExaminar(float angle) {
    examinar_angle_y += angle;
}


void Camara::resetOrientation() {
    examinar_angle_x = 0;
    examinar_angle_y = 0;
    observer_angle_x = 0;
    observer_angle_y = 0;
}