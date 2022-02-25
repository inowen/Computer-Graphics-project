#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "material.h"
#include "materialregistry.h"
#include "chasisconpatas.h"
#include "cola.h"
#include "aspas.h"
#include "colaconaspas.h"
#include "basehelicoptero.h"
#include "helicoptero.h"
#include "cubo_texturizado.h"
#include "math_helper.h"
#include <iostream>
#include <fstream>

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

   // Luces de la escena
   luna = new Luna(GL_LIGHT0); 
   direccional_cabeza = new LuzDireccional(Tupla2f(-90, 0), GL_LIGHT1,
               Tupla4f(0,0,0,0), Tupla4f(1,1,1,1), Tupla4f(1,1,1,1));

   // Luces
   for (int i=0; i<8; ++i) {
      this->luces[i] = false;
   }
   this->luces[0] = true;

   // Para hacer que la tierra brille un poco cuando le de la luz de la luna
   glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
   GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   // Objetos
   helicoptero = new Helicoptero();

   tierra = new Esfera(20, 20, 1, true, true);
   tierra->setTextura(new Textura("tierra.jpg"));
   tierra->calcularCoordTextura();

   mona_lisa = new CuboTexturizado(1);
   mona_lisa->setTextura(new Textura("mona_lisa_cubemap.jpg"));

}

Escena::~Escena() {
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   // Crear cámaras (ahora que se conocen los valores Width y Height)
   Camara por_defecto(1, Tupla3f(0,0,Observer_distance), Tupla3f(0,0,0), 
      Tupla3f(0,1,0), -Width, Width, -Height, Height, Front_plane, Back_plane);
   cams.push_back(por_defecto);
   Camara seguir_luna(1, Tupla3f(pos_luna(0), pos_luna(1)+50, pos_luna(2)+320),
      pos_luna, Tupla3f(0,1,0), -Width, Width, -Height, Height, Front_plane, Back_plane);
   seguir_luna.resetOrientation();
   cams.push_back(seguir_luna);
   Camara top_down(0, Tupla3f(0,250,0), Tupla3f(0,0,0), Tupla3f(0,0,-1),
      -Width, Width, -Height, Height, Front_plane, Back_plane);
   cams.push_back(top_down);

   for (int i=0; i<3; ++i) {
      objetos_enfocados.push_back(ObjetoEscena::_BACKGROUND);
   }
   

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}


// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

   // Ejes, sin iluminación
   glDisable(GL_LIGHTING);
   ejes.draw();

   glMatrixMode(GL_MODELVIEW);

   // Luces o no 
   glDisable(GL_LIGHTING);
   if (modo_iluminacion) {
      glEnable(GL_LIGHTING);
   }

   // Texturas o no
   glDisable(GL_TEXTURE_2D);
   if (modo_iluminacion) {
      glEnable(GL_TEXTURE_2D);
   }

   // Modo sombreado suave o no
   if (activar_sombreado_suave) {
      glShadeModel(GL_SMOOTH);
   }
   else {
      glShadeModel(GL_FLAT);
   }

   // Activar Luces:
   if (this->luces[1])
      direccional_cabeza->activar();
   else 
      direccional_cabeza->desactivar();

   // Modos líneas, sólido, ajedrez 
   if (activar_ajedrez && !modo_iluminacion) {
      glPolygonMode(GL_FRONT, GL_FILL);
      dibujarFiguras(true, modo_dibujar); 
   }

   if (activar_solido || modo_iluminacion) {
      glPolygonMode(GL_FRONT, GL_FILL);
      dibujarFiguras(false, modo_dibujar, VERDE);
   }

   if (activar_lineas && !modo_iluminacion) {
      glPolygonMode(GL_FRONT, GL_LINE);
      dibujarFiguras(false, modo_dibujar, AZUL);
   }

   if (activar_puntos && !modo_iluminacion) {
      glPolygonMode(GL_FRONT, GL_POINT);
      dibujarFiguras(false, modo_dibujar, ROJO);
   }


   // Extraer matriz modelo responsable de posicionar a la Luna
   glPushMatrix();
      glLoadIdentity();
      glTranslatef(0, 40, 0);
      glRotatef(angulo_rotacion_luna, 0,1,0);
      glTranslatef(150, -120, 0);
      glGetFloatv(GL_MODELVIEW_MATRIX, matriz_luna);
      pos_luna = MathHelper().multMatriz4f(matriz_luna, Tupla3f(0,0,0));
   glPopMatrix();

   // Actualizar posición de las cámaras que siguen a la Luna
   for (int i=0; i<3; ++i) {
      if (objetos_enfocados[i]==ObjetoEscena::_LUNA) {
         cams[i].setEye(Tupla3f(pos_luna(0), pos_luna(1)+60, pos_luna(2)+60));
         cams[i].setAt(pos_luna);
      }
   }
}

/*
 * Posiciona y dibuja las figuras donde les corresponda estar.
 */
void Escena::dibujarFiguras(bool modo_ajedrez, modoDibujado modo_dibujar, color color) {
   glPushMatrix();
      glTranslatef(0, 40, 0);
      glPushMatrix();
         glScalef(30,30,30);
         helicoptero->setColor(color);
         helicoptero->draw(modo_dibujar, modo_ajedrez);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0, -140, 0);
         glScalef(100,100,100);
         glRotatef(180, 0,0,1);
         glRotatef(90, 0,1,0);
         tierra->setColor(color);
         tierra->setMaterial(MaterialRegistry().especular_tierra);
         tierra->draw(modo_dibujar, modo_ajedrez);
      glPopMatrix();
      glPushMatrix();
         glRotatef(angulo_rotacion_luna, 0,1,0);
         glTranslatef(150, -120, 0);
         glScalef(20, 20, 20);
         luna->setColor(color);
         luna->draw(modo_dibujar, modo_ajedrez, luces[0]);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-500);
         glScalef(600,600,10);
         glRotatef(180, 0,0,1);
         mona_lisa->setColor(color);
         mona_lisa->draw(modo_dibujar, modo_ajedrez);
      glPopMatrix();
   glPopMatrix();
}

/**
 * Función de dibujado que da colores distintos a todos los 
 * objetos, para identificar sobre cuál se hace click.
 */
void Escena::dibujarSeleccion() {
   // Disable dither, colores 255, etc.
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
   glPushMatrix();
      glTranslatef(0, 40, 0);
      glPushMatrix();
         glScalef(30,30,30);
         helicoptero->setColor(HELICOPTERO);
         helicoptero->draw(INMEDIATO, false);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0, -140, 0);
         glScalef(100,100,100);
         glRotatef(180, 0,0,1);
         glRotatef(90, 0,1,0);
         tierra->setColor(TIERRA);
         tierra->setMaterial(MaterialRegistry().especular_tierra);
         tierra->draw(INMEDIATO, false);
      glPopMatrix();
      glPushMatrix();
         glRotatef(angulo_rotacion_luna, 0,1,0);
         glTranslatef(150, -120, 0);
         glScalef(20, 20, 20);
         luna->setColor(LUNA);
         luna->draw(INMEDIATO, false, luces[0]);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,-500);
         glScalef(600,600,10);
         glRotatef(180, 0,0,1);
         mona_lisa->setColor(MONALISA);
         mona_lisa->draw(INMEDIATO, false);
      glPopMatrix();
   glPopMatrix();
   glEnable(GL_DITHER);
}


// Propagar el tick de animación a cada uno de los objetos a animar
void Escena::tickAnimacion() {
   if (modoMenu == ANIM_AUTOMATICA) {
      helicoptero->tickAnimacion(
         multiplicador_velocidad_animacion, 
         multiplicador_velocidad_aspas,
         multiplicador_velocidad_puertas,
         multiplicador_velocidad_ventanas
      );
   }
   else if (modo_iluminacion && animando_luna) {
      angulo_rotacion_luna += 1.0f;
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   float incremento_ang_foco = 5.0f; // Incremento de alfa / beta, en grados sexagesimales
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA) {
            // Imprimir las opciones de menú
            printf("\t\tV: Selección de modo de visualización \n");
            printf("\t\tD: Selección de modo de dibujado\n");
            printf("\t\tI: Opciones de iluminación\n");
            printf("\t\tA: Animación automática\n");
            printf("\t\tM: Animación manual\n");
            printf("\t\tC: Selección de la cámara\n");
            modoMenu=NADA;
         }
         else {
            salir=true;
         }
         break ;
        case 'C':
         std::cout << "-- Modo selección de cámaras --" << std::endl;
         std::cout << "\tSeleccionar cámara con las teclas 0 a 2" << std::endl;
         modoMenu = SELECCIONAR_CAMARA;
         break;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         printf("Seleccionar modo de visualización: \n\
         \tP: Puntos\n\
         \tL: Líneas\n\
         \tS: Sólido\n\
         \tA: Ajedrez\n\
         \tT: Tapas\n\
         \tI: Iluminación\n\
         ");
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         printf("Seleccionar modo de dibujado: \n\
         \t1: Modo inmediato\n\
         \t2: Modo diferido\n");
         modoMenu=SELDIBUJADO;
         break ;
      case 'I':
         if (modoMenu=SELVISUALIZACION) {
            modo_iluminacion = !modo_iluminacion;
            std::cout << (modo_iluminacion ? "A" : "Desa") << "ctivando iluminación." << std::endl;
            if (modo_iluminacion) {
               modoMenu = ILUMINACION;
               std::cout << "\t0-7: Activar-desactivar luces 0-7" << std::endl;
               std::cout << "\tA: Activar ángulo alfa (alrededor del eje Y)" << std::endl;
               std::cout << "\tB: Activar ángulo beta (alrededor del eje X)" << std::endl;
               std::cout << "\t<: Decrementar ángulo activo" << std::endl;
               std::cout << "\t>: Incrementar ángulo activo" << std::endl;
               std::cout << "\tS: Activar/Desactivar modo sombreado suave" << std::endl;
               std::cout << "\tP: Activar/Desactivar animación automática de la luz puntual (luna)" 
                         << std::endl;
            }
         }
         break;
      case 'B': 
         if (modoMenu==ILUMINACION) {
            variando_alfa = false;
            std::cout << "Ahora variando beta de la luz (eje X)." << std::endl;
         }
         break; 
      case '<': 
         if (variando_alfa && modo_iluminacion) {
            direccional_cabeza->variarAnguloAlpha(-incremento_ang_foco);
         }
         else if (!variando_alfa && modo_iluminacion) {
            direccional_cabeza->variarAnguloBeta(-incremento_ang_foco);
         }
         break; 
      case '>': 
         if (variando_alfa  && modo_iluminacion) {
            direccional_cabeza->variarAnguloAlpha(incremento_ang_foco);
         }
         else if (!variando_alfa && modo_iluminacion) {
            direccional_cabeza->variarAnguloBeta(incremento_ang_foco);
         }
         break; 
      case '+':
         if (modoMenu == ANIM_AUTOMATICA) {
            float velocidad_imprimir;
            std::string item_imprimir;
            switch (item_editando_velocidad) {
               case NINGUNO:
                  multiplicador_velocidad_animacion += 0.5f;
                  velocidad_imprimir = multiplicador_velocidad_animacion;
                  item_imprimir = "general";
                  break;
               case VENTANAS:
                  multiplicador_velocidad_ventanas += 0.5f;
                  velocidad_imprimir = multiplicador_velocidad_ventanas;
                  item_imprimir = "de las ventanas";
                  break;
               case PUERTAS:
                  multiplicador_velocidad_puertas += 0.5f;
                  velocidad_imprimir = multiplicador_velocidad_puertas;
                  item_imprimir = "de las puertas";
                  break;
               case ASPAS:
                  multiplicador_velocidad_aspas += 0.5f;
                  velocidad_imprimir = multiplicador_velocidad_aspas;
                  item_imprimir = "de las aspas";
                  break;
            }
            std::cout << "Velocidad de animación " << item_imprimir
                      << " aumentado a " << velocidad_imprimir << std::endl;
         }
         else if (modoMenu == ANIM_MANUAL) {
            switch (item_animar)
            {
            case ASPAS:
               helicoptero->moverAspas(2);
               break;
            case PUERTAS:
               helicoptero->moverPuertas(INC_ANIM_MANUAL);
               break;
            case VENTANAS:
               helicoptero->moverVentanas(INC_ANIM_MANUAL);
               break;
            }
         }
         break;
      case '-':
         if (modoMenu == ANIM_MANUAL) {
            switch (item_animar)
            {
            case ASPAS:
               helicoptero->moverAspas(-2);
               break;
            case PUERTAS:
               helicoptero->moverPuertas(-INC_ANIM_MANUAL);
               break;
            case VENTANAS:
               helicoptero->moverVentanas(-INC_ANIM_MANUAL);
               break;
            }
         }
         else if (modoMenu == ANIM_AUTOMATICA) {
            float velocidad_imprimir;
            std::string item_imprimir;
            switch (item_editando_velocidad) {
               case NINGUNO:
                  multiplicador_velocidad_animacion -= 0.5f;
                  if (multiplicador_velocidad_animacion < 0) {
                     multiplicador_velocidad_animacion = 0;
                  }
                  velocidad_imprimir = multiplicador_velocidad_animacion;
                  item_imprimir = "general";
                  break;
               case VENTANAS:
                  multiplicador_velocidad_ventanas -= 0.5f;
                  if (multiplicador_velocidad_ventanas < 0) {
                     multiplicador_velocidad_ventanas = 0;
                  }
                  velocidad_imprimir = multiplicador_velocidad_ventanas;
                  item_imprimir = "de las ventanas";
                  break;
               case PUERTAS:
                  multiplicador_velocidad_puertas -= 0.5f;
                  if (multiplicador_velocidad_puertas < 0) {
                     multiplicador_velocidad_puertas = 0;
                  }
                  velocidad_imprimir = multiplicador_velocidad_puertas;
                  item_imprimir = "de las puertas";
                  break;
               case ASPAS:
                  multiplicador_velocidad_aspas -= 0.5f;
                  if ( multiplicador_velocidad_aspas< 0) {
                     multiplicador_velocidad_aspas = 0;
                  }
                  velocidad_imprimir = multiplicador_velocidad_aspas;
                  item_imprimir = "de las aspas";
                  break;
            }
            std::cout << "Velocidad de animación " << item_imprimir
                      << " aumentado a " << velocidad_imprimir << std::endl;
         }
         break;


         // COMPLETAR con los diferentes opciones de teclado
       case 'T':
         if (modoMenu == SELVISUALIZACION) {
            activar_tapas = !activar_tapas;
            std::cout << (activar_tapas ? "A" : "Desa") << "ctivando tapas." << std::endl;
         }
         break;
       case 'P':
         if (modoMenu == SELVISUALIZACION && !modo_iluminacion) {
            activar_puntos = !activar_puntos;
            std::cout << (activar_puntos ? "A" : "Desa") << "ctivando puntos." << std::endl;
         }
         else if (modoMenu==ILUMINACION) {
            // Activar o desactivar animación automática de la luz
            animando_luna = !animando_luna;
            std::cout << (animando_luna ? "A" : "Desa")
                      << "ctivando animación automática de la luna"
                      << std::endl;
         }
         
         break;
       case 'L':
         if (modoMenu == SELVISUALIZACION) {
            activar_lineas = !activar_lineas;
            std::cout << (activar_lineas ? "A" : "Desa") << "ctivando lineas." << std::endl;
         }
         break;
       case 'S':
         if (modoMenu == SELVISUALIZACION) {
            if (!modo_iluminacion) {
               activar_solido = !activar_solido;
               activar_ajedrez = false;
               std::cout << (activar_solido ? "A" : "Desa") << "ctivando sólido." << std::endl;
            }
         }
         if (modoMenu == ILUMINACION) {
            this->activar_sombreado_suave = !this->activar_sombreado_suave;
            std::cout << (activar_sombreado_suave ? "A" : "Desa") 
                     << "ctivado sombreado suave" << std::endl;
         }
         break;
       case 'A':
         if ((modoMenu == SELVISUALIZACION) && !modo_iluminacion) {
            activar_ajedrez = !activar_ajedrez; 
            activar_solido = false;
            std::cout << (activar_ajedrez ? "A" : "Desa") << "ctivando ajedrez." << std::endl;
         }
         else if ((modoMenu == SELVISUALIZACION) && modo_iluminacion) {
            variando_alfa = true;
            std::cout << "Ahora variando alfa de la luz (eje Y)." << std::endl;
         }
         else if (modoMenu == NADA) {
            std::cout << "Activando animación automática." << std::endl;
            std::cout << "\t+: Aumentar velocidad de la animación." << std::endl;
            std::cout << "\t-: Reducir velocidad de la animación." << std::endl;
            std::cout << "\t0: Editar velocidad del movimiento de ventanas." << std::endl;
            std::cout << "\t1: Editar velocidad del movimiento de puertas." << std::endl;
            std::cout << "\t2: Editar velocidad del movimiento de aspas." << std::endl;
            std::cout << "\t3: Editar velocidad de la animación en general." << std::endl;
            multiplicador_velocidad_animacion = 1.0f; // Resetea velocidad
            modoMenu = ANIM_AUTOMATICA;
         }
         break;
       case '0':
         if (modoMenu == ILUMINACION) {
            std::cout << (this->luces[0] ? "Desh" : "H") << "abilitando luz 0." << std::endl;
            this->luces[0] = !this->luces[0];
         }
         else if (modoMenu == ANIM_MANUAL) {
            item_animar = VENTANAS;
            std::cout << "Ventanas seleccionadas para animación." << std::endl;
         }
         else if (modoMenu == ANIM_AUTOMATICA) {
            item_editando_velocidad = VENTANAS;
            std::cout << "Use teclas +/- para editar velocidad de animación de ventanas."<<std::endl;
         }
         else if (modoMenu == SELECCIONAR_CAMARA) {
            std::cout << "Activando cámara 0" << std::endl;
            cam_actual = 0;
         }
         break;
       case '1':
         if (modoMenu == SELDIBUJADO) {
            modo_dibujar = INMEDIATO;
            std::cout << "Activando modo de dibujado inmediato" << std::endl;
         }
         else if (modoMenu == ILUMINACION) {
            std::cout << (this->luces[1] ? "Desh" : "H") << "abilitando luz 1." << std::endl;
            this->luces[1] = !this->luces[1];
         }
         else if (modoMenu == ANIM_MANUAL) {
            item_animar = PUERTAS;
            std::cout << "Puertas seleccionadas para animación." << std::endl;
         }
         else if (modoMenu == ANIM_AUTOMATICA) {
            item_editando_velocidad = PUERTAS;
            std::cout << "Use teclas +/- para editar velocidad de animación de puertas."<<std::endl;
         }
         else if (modoMenu == SELECCIONAR_CAMARA) {
            std::cout << "Activando cámara 1" << std::endl;
            cam_actual = 1;
         }
         break;
       case '2':
         if (modoMenu == SELDIBUJADO) {
            modo_dibujar = DIFERIDO;
            std::cout << "Activando modo de dibujado diferido" << std::endl;
         }
         else if (modoMenu == ILUMINACION) {
            std::cout << (this->luces[2] ? "Desh" : "H") << "abilitando luz 2." << std::endl;
            this->luces[2] = !this->luces[2];
         }
         else if (modoMenu == ANIM_MANUAL) {
            item_animar = ASPAS;
            std::cout << "Aspas seleccionadas para animación." << std::endl;
         }
         else if (modoMenu == ANIM_AUTOMATICA) {
            item_editando_velocidad = ASPAS;
            std::cout << "Use teclas +/- para editar velocidad de animación de aspas."<<std::endl;
         }
         else if (modoMenu == SELECCIONAR_CAMARA) {
            std::cout << "Activando cámara 2" << std::endl;
            cam_actual = 2;
         }
         break;
      case '3':
         if (modoMenu == ANIM_AUTOMATICA) {
            item_editando_velocidad = NINGUNO;
            std::cout << "Use teclas +/- para editar velocidad de animación general."<<std::endl;
         }
         break;
      case 'M':
         if (modoMenu == NADA) {
            std::cout << "Activando animación manual." << std::endl;
            std::cout << "\t0: Animar ventanas." << std::endl;
            std::cout << "\t1: Animar puertas." << std::endl;
            std::cout << "\t2: Animar aspas." << std::endl;
            std::cout << "\t+: Aumentar valor del grado de libertad seleccionado." << std::endl;
            std::cout << "\t-: Disminuir valor del grado de libertad seleccionado" << std::endl;
            modoMenu = ANIM_MANUAL;
         }
         break;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   const float PI = 3.1415926535;
   float one_degree_in_rads = PI/180.0f;
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         if (objetos_enfocados[cam_actual] == _BACKGROUND) {
            cams[cam_actual].rotarYFirstPerson(-1);
         }
         else {
            cams[cam_actual].rotarYExaminar(-1);
         }
         break;
	   case GLUT_KEY_RIGHT:
         if (objetos_enfocados[cam_actual] == _BACKGROUND) {
            cams[cam_actual].rotarYFirstPerson(1);
         }
         else {
            cams[cam_actual].rotarYExaminar(1);
         }
         break;
	   case GLUT_KEY_UP:
         if (objetos_enfocados[cam_actual] == _BACKGROUND) {
            cams[cam_actual].rotarXFirstPerson(-1);
         }
         else {
            cams[cam_actual].rotarXExaminar(-1);
         }
         break;
	   case GLUT_KEY_DOWN:
         if (objetos_enfocados[cam_actual] == _BACKGROUND) {
            cams[cam_actual].rotarXFirstPerson(1);
         }
         else {
            cams[cam_actual].rotarXExaminar(1);
         }
         break;
	   case GLUT_KEY_PAGE_UP:
         cams[cam_actual].zoom(3);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         cams[cam_actual].zoom(-3);
         break;
	}
}

// Uso del ratón 
void Escena::clickRaton(int boton, int estado, int x, int y) {
   if (boton == GLUT_LEFT_BUTTON && estado == GLUT_UP) {
      mouse_status = (estado==GLUT_DOWN ? LEFT_DOWN : NONE);
      // La selección
      ObjetoEscena obj_clicado = getObjetoEn(x,y);
      // El switch, poner eye y at para cada cosa.
      // ...Poner booleano en el vector si es la Luna!!
      switch (obj_clicado) {
         case _LUNA:
            cams[cam_actual].resetOrientation();
            cams[cam_actual].setAt(pos_luna);
            cams[cam_actual].setEye(Tupla3f(pos_luna(0), pos_luna(1)+60, pos_luna(2)+60));
            cams[cam_actual].setObserverDistance(20);
            objetos_enfocados[cam_actual] = ObjetoEscena::_LUNA;
            break;
         case _TIERRA: {
            cams[cam_actual].resetOrientation();
            cams[cam_actual].setAt(pos_tierra);
            Tupla3f tierra_eye = pos_tierra;
            tierra_eye(2) += 100;
            cams[cam_actual].setEye(tierra_eye);
            cams[cam_actual].setObserverDistance(100);
            objetos_enfocados[cam_actual] = ObjetoEscena::_TIERRA;
            break;
         }
         case _MONALISA: {
            cams[cam_actual].resetOrientation();
            cams[cam_actual].setAt(pos_monalisa);
            Tupla3f ml_eye = pos_monalisa;
            ml_eye(2)+= 100; ml_eye(1) += 10;
            cams[cam_actual].setEye(ml_eye);
            cams[cam_actual].setObserverDistance(120);
            objetos_enfocados[cam_actual] = ObjetoEscena::_MONALISA;
            break;
         }
         case _HELICOPTERO: {
            cams[cam_actual].resetOrientation();
            cams[cam_actual].setAt(pos_helicoptero);
            Tupla3f heli_eye = pos_helicoptero;
            heli_eye(2) += 100;
            heli_eye(1) += 60;
            cams[cam_actual].setEye(heli_eye);
            cams[cam_actual].setObserverDistance(15);
            objetos_enfocados[cam_actual] = ObjetoEscena::_HELICOPTERO;
            break;
         }
         case _BACKGROUND:
            objetos_enfocados[cam_actual] = ObjetoEscena::_BACKGROUND;
            break;
      }

   }
   else if (boton == GLUT_RIGHT_BUTTON) {
      mouse_status = (estado==GLUT_DOWN ? RIGHT_DOWN : NONE);
      if (mouse_status == RIGHT_DOWN) {
         mouse_last_x = x;
         mouse_last_y = y;
      }
   }
   // Mouse wheel, 4 = upwards, 3 = downwards
   else if (boton==3 || boton==4) {
      cams[cam_actual].zoom(boton==4 ? 2 : -2);
   }
}

// Detectar qué objeto hay en un píxel de la pantalla dado
ObjetoEscena Escena::getObjetoEn(int x, int y) {
   dibujarSeleccion();
   GLubyte res[3];
   glReadPixels(x,10*Height-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&res); 
   Tupla3ub p(res[0], res[1], res[2]); // color pix. seleccionado
   Tupla3ub l = colores_seleccion().luna; // color luna
   Tupla3ub m = colores_seleccion().monalisa;
   Tupla3ub h = colores_seleccion().helicoptero;
   Tupla3ub t = colores_seleccion().tierra;
   if (p(0)==l(0)&&p(1)==l(1)&&p(2)==l(2)) {
      return ObjetoEscena::_LUNA;
   }
   else if (p(0)==m(0)&&p(1)==m(1)&&p(2)==m(2)) {
      return ObjetoEscena::_MONALISA;
   }
   else if (p(0)==h(0)&&p(1)==h(1)&&p(2)==h(2)) {
      return ObjetoEscena::_HELICOPTERO;
   }
   else if (p(0)==t(0)&&p(1)==t(1)&&p(2)==t(2)) {
      return ObjetoEscena::_TIERRA;
   }
   else {
      return ObjetoEscena::_BACKGROUND;
   }
}

void Escena::ratonMovido(int x, int y) {
   if (mouse_status == MouseStatus::RIGHT_DOWN) {
      // Calcular desplazamiento
      int x_offset = x - mouse_last_x;
      int y_offset = y - mouse_last_y;
      float angle_x = -y_offset/8.0f;
      float angle_y = -x_offset/8.0f;
      if (objetos_enfocados[cam_actual]==_BACKGROUND) {
         // Girar FP
         cams[cam_actual].rotarXFirstPerson(angle_x);
         cams[cam_actual].rotarYFirstPerson(angle_y);
      }
      else {
         // Girar en modo examinar
         cams[cam_actual].rotarXExaminar(angle_x);
         cams[cam_actual].rotarYExaminar(angle_y);
      }
      mouse_last_x = x;
      mouse_last_y = y;
   }
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   cams[cam_actual].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   // Adaptar parámetros del frustum para no distorsionar
   for (int i=0; i<cams.size(); ++i) {
      cams[i].setLeft(-Width);
      cams[i].setRight(Width);
      cams[i].setBottom(-Height);
      cams[i].setTop(Height);
   }
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   cams[cam_actual].setObserver();
}

