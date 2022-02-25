// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "menus.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:
   Malla3D();
   ~Malla3D();
   void draw(modoDibujado modo_dibujado, bool modo_ajedrez) ;
   void setColor(color c);
   void setMaterial(Material m) {material=m;}
   void setTextura(Textura* tex) {textura=tex;}


   protected:
   void draw_ModoInmediato();
   void draw_ModoDiferido();
   void draw_Ajedrez(modoDibujado modo_dibujado);
   void draw_Ajedrez_Inmediato();
   void draw_Ajedrez_Diferido();

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   void init_pares_impares(); // Para los dos vectores de caras del modo ajedrez

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3u> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> nv; // Normales de los vértices
   std::vector<Tupla2f> ct; // Coordenadas de texturas

   GLuint id_vbo_v = 0, id_vbo_f_pares = 0, id_vbo_f_impares = 0, id_vbo_colores = 0;
   GLuint id_vbo_rojo = 0, id_vbo_verde = 0, id_vbo_f = 0;
   GLuint id_vbo_normales = 0;
   GLuint id_vbo_texturas = 0;
   std::vector<Tupla3u> f_pares;
   std::vector<Tupla3u> f_impares;
   Textura* textura = nullptr;

   // Vectores de colores: rojo, verde, azul
   std::vector<Tupla3f> rojo;
   std::vector<Tupla3f> verde;
   std::vector<Tupla3f> azul;
   std::vector<Tupla3ub> sel_tierra;
   std::vector<Tupla3ub> sel_luna;
   std::vector<Tupla3ub> sel_monalisa;
   std::vector<Tupla3ub> sel_helicoptero;
   color color_dibujado = VERDE;
   
   // Material
   Material material;
} ;


#endif
