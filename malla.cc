#include "aux.h"
#include "malla.h"
#include <iostream>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************
Malla3D::Malla3D() {
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
   glPointSize(3.0f);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   void* color_pointer;
   switch (color_dibujado) {
      case ROJO:
         color_pointer = rojo.data();
         break;
      case VERDE:
         color_pointer = verde.data();
         break;
      case AZUL:
         color_pointer = azul.data();
         break;
      case TIERRA:
         color_pointer = sel_tierra.data();
         break;
      case LUNA:
         color_pointer = sel_luna.data();
         break;
      case HELICOPTERO:
         color_pointer = sel_helicoptero.data();
         break;
      case MONALISA:
         color_pointer = sel_monalisa.data();
         break;
   }
   if (color_dibujado==ROJO || color_dibujado==VERDE || color_dibujado==AZUL) {
      glColorPointer(3, GL_FLOAT, 0, color_pointer);
   }
   else {
      glColorPointer(3, GL_UNSIGNED_BYTE, 0, color_pointer);
   }
   glNormalPointer(GL_FLOAT, 0, this->nv.data());
   glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{  
   // Inicializar Vbo para vértices
   if (id_vbo_v == 0) {
      glGenBuffers(1, &id_vbo_v);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Tupla3f)*v.size(), v.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   // Inicializar Vbo para caras
   if (id_vbo_f == 0) {
      glGenBuffers(1, &id_vbo_f);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tupla3u)*f.size(), f.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }

   // Inicializar Vbo para normales
   if (id_vbo_normales == 0) {
      glGenBuffers(1, &id_vbo_normales);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Tupla3f)*nv.size(), nv.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   // Inicializar Vbo para coordenadas de textura
   if (id_vbo_texturas == 0) {
      glGenBuffers(1, &id_vbo_texturas);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_texturas);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Tupla2f)*ct.size(), ct.data(), GL_STATIC_DRAW);
   }


   // DIBUJAR
   glEnableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   void* color_pointer;
   switch (color_dibujado) {
      case ROJO:
         color_pointer = rojo.data();
         break;
      case VERDE:
         color_pointer = verde.data();
         break;
      case AZUL:
         color_pointer = azul.data();
         break;
      case TIERRA:
         color_pointer = sel_tierra.data();
         break;
      case LUNA:
         color_pointer = sel_luna.data();
         break;
      case HELICOPTERO:
         color_pointer = sel_helicoptero.data();
         break;
      case MONALISA:
         color_pointer = sel_monalisa.data();
         break;
   }
   glColorPointer(3, GL_FLOAT, 0, color_pointer);
   glEnableClientState(GL_VERTEX_ARRAY);

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales);
   glNormalPointer(GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   if (textura != nullptr && ct.size()>=v.size()) {
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_texturas);
      glTexCoordPointer(2, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }


   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f);
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modoDibujado modo_dibujado, bool modo_ajedrez)
{
   // Calcular normales
   if (nv.empty()) {
      calcular_normales();
   }

   if (modo_ajedrez) {
      draw_Ajedrez(modo_dibujado);
   }
   else {
      // Textura
      if (textura != nullptr && ct.size()>=v.size()) {
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         textura->activar();
      }
      else {
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      }
      setColor(color_dibujado);
      material.aplicar();
      if (modo_dibujado == INMEDIATO) {
         draw_ModoInmediato();
      }
      else if (modo_dibujado == DIFERIDO) {
         draw_ModoDiferido();
      }
   }
}

void Malla3D::setColor(color c) {
   Tupla3f color_asociado;
   Tupla3ub color_asociadou;
   bool ya_init = false;
   std::vector<Tupla3f>* arr_color = nullptr;
   std::vector<Tupla3ub>* arr_coloru = nullptr;
   switch(c) {
      case ROJO:
         color_asociado = Tupla3f(1.0f, 0.0f, 0.0f);
         ya_init = !rojo.empty();
         arr_color = &rojo;
         break;
      case VERDE:
         color_asociado = Tupla3f(0.0f, 1.0f, 0.0f);
         ya_init = !verde.empty();
         arr_color = &verde;
         break;
      case AZUL:
         color_asociado = Tupla3f(0.0f, 0.0f, 1.0f);
         ya_init = !azul.empty();
         arr_color = &azul;
         break;
      case TIERRA:
         color_asociadou = colores_seleccion().tierra;
         ya_init = !sel_tierra.empty();
         arr_coloru = &sel_tierra;
         break;
      case LUNA:
         color_asociadou = colores_seleccion().luna;
         ya_init = !sel_luna.empty();
         arr_coloru = &sel_luna;
         break;
      case MONALISA:
         color_asociadou = colores_seleccion().monalisa;
         ya_init = !sel_monalisa.empty();
         arr_coloru = &sel_monalisa;
         break;
      case HELICOPTERO:
         color_asociadou = colores_seleccion().helicoptero;
         ya_init = !sel_helicoptero.empty();
         arr_coloru = &sel_helicoptero;
         break;
   }
   if (!ya_init) {
      for (int i=0; i<v.size(); ++i) {
         if (arr_color != nullptr)
            arr_color->push_back(color_asociado);
         if (arr_coloru != nullptr)
            arr_coloru->push_back(color_asociadou);
      }
   }
   color_dibujado = c;
}

void Malla3D::draw_Ajedrez(modoDibujado modo_dibujado) {
   if (f_pares.size() == 0) {
      init_pares_impares();
   }
   if (modo_dibujado == INMEDIATO) {
      draw_Ajedrez_Inmediato();
   }
   else if (modo_dibujado == DIFERIDO) {
      draw_Ajedrez_Diferido();
   }
}

void Malla3D::draw_Ajedrez_Inmediato() {
   this->setColor(ROJO);
   glEnableClientState(GL_COLOR_ARRAY);
   glEnableClientState(GL_VERTEX_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, rojo.data());
   glVertexPointer(3, GL_FLOAT, 0, v.data()); 
   glDrawElements(GL_TRIANGLES, 3*f_pares.size(), GL_UNSIGNED_INT, f_pares.data()); 
   this->setColor(VERDE);
   glColorPointer(3, GL_FLOAT, 0, verde.data());
   glDrawElements(GL_TRIANGLES, 3*f_impares.size(), GL_UNSIGNED_INT, f_impares.data());
}

void Malla3D::draw_Ajedrez_Diferido() {
   // Poner buffer de vértices si no está definido
   if (id_vbo_v == 0) { 
      glGenBuffers(1, &id_vbo_v);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v);
      glBufferData(GL_ARRAY_BUFFER, v.size()*sizeof(Tupla3f), v.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   // Poner buffer de índices pares si no está definido
   if (id_vbo_f_pares == 0) {
      glGenBuffers(1, &id_vbo_f_pares);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_pares);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, f_pares.size()*sizeof(Tupla3u), f_pares.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }


   // Poner buffer de índices impares si no está definido
   if (id_vbo_f_impares == 0) {
      glGenBuffers(1, &id_vbo_f_impares);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_impares);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, f_impares.size()*sizeof(Tupla3u), f_impares.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }


   // Crear buffer de color rojo si no está definido
   if (id_vbo_rojo == 0) {
      this->setColor(ROJO);
      glGenBuffers(1, &id_vbo_rojo);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_rojo);
      glBufferData(GL_ARRAY_BUFFER, rojo.size()*sizeof(Tupla3f), rojo.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   // Crear buffer de color verde si no está definido
   if (id_vbo_verde == 0) {
      this->setColor(VERDE);
      glGenBuffers(1, &id_vbo_verde);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_verde);
      glBufferData(GL_ARRAY_BUFFER, verde.size()*sizeof(Tupla3f), verde.data(), GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   // DIBUJAR
   glPolygonMode(GL_FRONT, GL_FILL);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   // Asignar vértices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v); 
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   // Asignar color rojo
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_rojo);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   // Dibujar caras de índice par
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_pares);
   glDrawElements(GL_TRIANGLES, 3*f_impares.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   // Asignar verde
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_verde);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   // Dibujar caras de índice impar
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_impares);
   glDrawElements(GL_TRIANGLES, f_impares.size()*3, GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Malla3D::init_pares_impares() {
   for (int i=0; i<f.size()-1; i+=2) {
      f_pares.push_back(f[i]);
      f_impares.push_back(f[i+1]);
   }
}

// Normales de los vértices
void Malla3D::calcular_normales() {
   this->nv.clear();
   for (int i=0; i<this->v.size(); ++i) {
      this->nv.push_back(Tupla3f(0,0,0));
   }
   
   for (Tupla3u cara: this->f) {
      // Calcular el producto vectorial asociado
      Tupla3f v0 = this->v[cara(0)];
      Tupla3f v1 = this->v[cara(1)];
      Tupla3f v2 = this->v[cara(2)];
      Tupla3f v1v0 = v1-v0, v2v0= v2-v0;
      Tupla3f cr = v1v0.cross(v2v0);

      // Acumularlo en los 3 vértices asociados
      for(int i=0; i<3; ++i) {
         this->nv[cara(i)] = cr + this->nv[cara(i)];
      }
   }

   for (int i=0; i<this->nv.size(); ++i) {
      if (this->nv[i].lengthSq() > 0) {
      this->nv[i] = this->nv[i].normalized();
      }
      else {
         this->nv[i] = Tupla3f(1,0,0);
      }
   }
}



Malla3D::~Malla3D() {
   delete textura;
}


