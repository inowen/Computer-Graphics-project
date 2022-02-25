// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, eje eje_rotacion=EJE_Y) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, eje eje_rotacion=EJE_Y) ;
   void calcularCoordTextura(); // Posterior a asignar una textura
private:
    bool tapa_sup=false, tapa_inf=false;
    int tam_perfil;
    const float PI = 3.1415926535;
    Tupla3f polo_norte, polo_sur;
    bool es_polo(Tupla3f, eje);
    Tupla3f hacer_polo(Tupla3f src, eje eje_rotacion);
    // Atributos del cuerpo, y cada una de las tapas.
    // Se calcula una vez, y luego se recompone según se activen tapas o no.

protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, eje eje_rotacion=EJE_Y, bool tapa_inf=true, bool tapa_sup=true);

} ;




#endif
