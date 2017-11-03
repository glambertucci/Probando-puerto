#ifndef R_PIN_H

#define R_PIN_H

#include <stdio.h>
#include "struct.h"

#define LED_1 ("4")		//Pines GPIO
#define LED_2 ("17")
#define LED_3 ("27")
#define LED_4 ("22")
#define LED_5 ("18")
#define LED_6 ("23")
#define LED_7 ("24")

//Las siguientes funciones son para el manejo de pines en el RASPBERRY PI

// Esta función cambia el estados de los pines seteados como salidas
//
// char *pin: es un puntero a un string que indica el pin GPIO
// char led_state: caracter 0 o 1 que indica el estado de OFF o ON del pin
void state_set(char * pin, char led_state);

// Esta funcion prepara los pines para ser utilizados en el Rasp pi
//
// void * pointer: puntero a la estructura que acompaña al manejo de estados de los pines
void set_leds (void * pointer);

// Esta funcion finaliza el uso de los pines
//
// No recibe parámetros
void unset_leds (void);

#endif /* LED_PRINT_H */
