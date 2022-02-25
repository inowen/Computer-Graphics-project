#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "objply.h"
#include "tetraedro.h"
#include "menus.h"
#include "objrevolucion.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include "material.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "helicoptero.h"
#include "luna.h"
#include "cubo_texturizado.h"
#include "camara.h"

class Escena
{
    public:
    Escena();
    ~Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
	void dibujar() ;
	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    // Animación automática
    void tickAnimacion();


    private:
    void dibujarFiguras(bool modo_ajedrez, modoDibujado modo_dibujar, color c=VERDE);
    void dibujarSeleccion();
    ObjetoEscena getObjetoEn(int x, int y);

    // Ratón 
    MouseStatus mouse_status = MouseStatus::NONE; 
    int mouse_last_x, mouse_last_y;

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    
    // Posiciones de cada uno de los objetos
    float matriz_luna[16];
    Tupla3f pos_luna = Tupla3f(150, -80, -200);
    Tupla3f pos_helicoptero = Tupla3f(0,40,0);
    Tupla3f pos_monalisa = Tupla3f(0,40,-500);
    Tupla3f pos_tierra = Tupla3f(0,-100,0);

   void clear_window();


   menu modoMenu = NADA;
   bool activar_lineas = false;
   bool activar_solido = true;
   bool activar_puntos = false;
   bool activar_ajedrez = false;
   bool activar_tapas = true;
   bool activar_tapas_anterior = true;
   modoDibujado modo_dibujar = INMEDIATO;
   bool modo_iluminacion = false;
   bool luces[8];
   bool animando_luna = false;
   float angulo_rotacion_luna = 0;
   bool activar_sombreado_suave = true;
   float multiplicador_velocidad_animacion = 1;
   float multiplicador_velocidad_puertas = 1;
   float multiplicador_velocidad_ventanas = 1;
   float multiplicador_velocidad_aspas = 1;
   itemAnimable item_animar = ASPAS; // En animación manual
   itemAnimable item_editando_velocidad = NINGUNO; // En animación automática
   // La proporción del rango total de movimiento en la que aumenta cada grado
   // de libertad en cada paso en el modo de animación manual.
   const float INC_ANIM_MANUAL = 0.05f;
   

   // Objetos de la escena
   Ejes ejes;
   Helicoptero * helicoptero = nullptr;
   Esfera * tierra = nullptr;
   Luna* luna = nullptr;
   CuboTexturizado* mona_lisa = nullptr;
   LuzDireccional * direccional_cabeza = nullptr;
   bool variando_alfa = true; // Del menú, ángulo alfa de la luz direccional

    std::vector<Camara> cams;
    int cam_actual = 0;
    // El objeto que mira cada cámara.
    std::vector<ObjetoEscena> objetos_enfocados;
};
#endif
