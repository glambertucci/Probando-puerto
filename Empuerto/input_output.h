#ifndef _INPUT_OUTPUT_H_
#define _INPUT_OUTPUT_H_


#include "define.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//Define para el display instructivo
#define TITLE (0)
#define INDIVIDUAL_LEDS (1)
#define BLINK (2)
#define ON (3)
#define OFF (4)
#define MOUSE (5)
#define BACKGROUND (6)
#define LEAVE (7)
#define INSTRUCTIONS (8)
#define MAX_MESSAGES (9)

// Se fija si al hacer click, tocaste algun boton. Si lo tocaste devuelve 'true', sino devuelve 'false'
//
// int mouse_x  :   Debe ser la coordenada en X de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// int mouse_y  :   Debe ser la coordenada en Y de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// int button_x :   Es la coordenada en X donde comienza el boton
// int button_y :   Es la coordenada en Y donde comienza el boton
// int lenght_x :   Es el largo en el eje X del boton
// int lenght_y :   Es la altura del boton en el eje Y
bool click_button(int mouse_x, int mouse_y, int button_x, int button_y , int lenght_x, int lenght_y );

// Dada una cantidad de botones que se le envia a la funcion, devuelve el valor (0 a (cantidad de elementos-1)) que identifica al boton
//
// int mouse_x  :   Debe ser la coordenada en X de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// int mouse_y  :   Debe ser la coordenada en Y de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// void * pointer2 : Debe ser un puntero al primer elemento de un arreglo de estructuras definidas con el typedef 'element' en el archivo 'define.h'
// int elements :   Es la cantidad de botones que hay en pantalla y que se quiere fijar si se han tocado
int button_pressed (int mouse_x, int mouse_y, void * pointer2, int elements);

// Esta funcion se encarga de imprimir en el display al fondo de pantalla y a todos los botones en su lugar
// La funcion tambien puede imprimir los bitmaps que  estan en la estructura de cada boton, pero para eso deben
// tener la opcion led_enabled en 'false'
//
// void * element_pointer : Debe ser un puntero al primer elemento de un arreglo de estructuras definidas con el typedef 'element' en el archivo 'define.h'
// void * background : Es un puntero que apunta a un bitmap de allegro, que contiene el fondo que se le va a aplicar
// void * led_on_void : Es un puntero que apunta a un bitmap de allegro, que se utiliza para mostrar que un led esta encendido
// void * led_off_void : Es un puntero que apunta a un bitmap de allegro, que se utiliza para mostrar que un led esta apagado
// int elements :   Es la cantidad de botones que hay en pantalla y que se quiere fijar si se han tocado
void print_display (void * element_pointer, void * background,void * led_on_void, void * led_off_void, int elementos);

// Esta funcion imprime las instrucciones del programa en un display distinto,
//
// IMPORTANTE : Esta funcion devuelve 0 si se ejecuto correctamente o devuelve -1 si no pudo cargar las funtes o crear la event queue
// 
// const char * archivo_letra_titulo : Debe ser un string constante que indique el nombre del archivo que contiene a la fuente que se desee usar (Ej. "poke.ttf")
// const char * archivo_letra_cuerpo : Debe ser un string constante que indique el nombre del archivo que contiene a la fuente que se desee usar (Ej. "poke.ttf")
// const char * color_letra : Debe ser un string constante que indique el color de la letra que se desea (Ej. "White")
int display_instructions (const char * archivo_letra_titulo, const char * archivo_letra_cuerpo, const char * color_letra);

// Esta funcion imprime las instrucciones del programa en el mismo display
// 
// const char * archivo_letra_titulo : Debe ser un string constante que indique el nombre del archivo que contiene a la fuente que se desee usar (Ej. "poke.ttf")
// const char * archivo_letra_cuerpo : Debe ser un string constante que indique el nombre del archivo que contiene a la fuente que se desee usar (Ej. "poke.ttf")
// const char * color_letra : Debe ser un string constante que indique el color de la letra que se desea (Ej. "White")
int print_instructions (const char * archivo_letra_titulo, const char * archivo_letra_cuerpo, const char * color_letra);


 #endif 
 // _INPUT_OUTPUT_H_