#ifndef _operations_
#define _operations_

#include "define.h"
#include "input_output.h"
#include <stdbool.h>
#define FPS2 (3)
#define ESPACIO_LAT (70)
#define ESPACIO_INT (20)
#define LARGO_X (90)
#define LARGO_Y (90)


#define ESPACIO_LAT_RECT (58)
#define ESPACIO_INT_RECT (58)
#define LARGO_RECT_X (256)
#define LARGO_RECT_Y (77)

// Esta funcion se encarga de cargar todos los datos necesarios en la estructura definida como 'element'
//
// void * element_pointer : Es un puntero a la estructura 'element', donde debera cargar los demas datos enviados
// bool led_on : Indica si el led va a estar encendido. debe ser  'true' o 'false'
// bool led_enabled : Indica si se trata de un led, de estar en 'true' se lo va a cargar como si fuese un led. Si esta en 'false' podra tener su bitmap propio y se comportara como un boton
// void * bitmap_pointer : Es un puntero al bitmap que se le cargara en caso de que led_enabled este desactivado. Si led_enabled esta activado debe ser NULL.
void init_coord (void * element_pointer ,bool led_on, bool led_enabled ,void * bitmap_pointer);

// Esta funcion apaga todos los leds. NO IMPRIME
//
// void * element_pointer : Es un puntero a un elemento de un arreglo de elements ( estructura que contiene toda la info de cada led o boton)
// int elementos : Es la cantidad de leds (no botones) que hay
void clr_all( void * element_pointer, int elementos);

// Esta funcion prende todos los leds. NO IMPRIME
//
// void * element_pointer : Es un puntero a un elemento de un arreglo de elements ( estructura que contiene toda la info de cada led o boton)
// int elementos : Es la cantidad de leds (no botones) que hay
void set_all( void * element_pointer, int elementos);

// Esta funcion hace que los leds parpadeen.
// IMPORTANTE : ESTA FUNCION IMPRIME EN EL DISPLAY USANDO LA FUNCION 'PRINT_DISPLAY'. NO ENCONTRAMOS FORMA DE 
//              SEPARARLO EN BACKEND Y FRONTEND QUE NO INVOLUCRARA COPIAR EL CONTENIDO DE ESTA FUNCION AL MAIN.
//
// void * element_pointer : Es un puntero a un elemento de un arreglo de elements ( estructura que contiene toda la info de cada led o boton)
// void * background : Es un puntero a un bitmap de allegro que sera enviado a PRINT_DISPLAY PARA IMPRIMIR EN PANTALLA. (Es el fondo de pantalla)
// void * led_on_void : Es un puntero a un bitmap de allegro que sera enviado a PRINT_DISPLAY PARA IMPRIMIR EN PANTALLA. (Es el bitmap del led encendido)
// void * led_off_void : Es un puntero a un bitmap de allegro que sera enviado a PRINT_DISPLAY PARA IMPRIMIR EN PANTALLA. (Es el bitmap del led apagado)
// int elementos : Es la cantidad de leds (no botones) que hay
// int repetir : Es la cantidad de veces que se van a parpadear
void blink_all(void * element_pointer, void * background,void * led_on_void, void * led_off_void,int elementos, int repetir);

// Esta funcion se encarga de invertir el estado de un led. Si esta prendido lo apaga y viceversa.
//
// void * element_pointer : Es un puntero a un elemento de un arreglo de elements ( estructura que contiene toda la info de cada led o boton)
void bit_switch (void * element_pointer);

#endif
