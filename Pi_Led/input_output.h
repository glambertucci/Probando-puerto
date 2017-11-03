#ifndef _INPUT_OUTPUT_H_
#define _INPUT_OUTPUT_H_

#include "struct.h"			// librerias no estandares para que las funciones compilen y corran
#include "operations.h"		// sin problemas.

#define LEDON '*'			// representan a los caracteres que se imprimen en terminal, si el led
#define LEDOFF '-'			// esta encendido o apagado.

#ifdef _WIN32
   #error "This program is only targeted at Linux systems"
#endif

//Funcion get_char: No recibe ningun parametro, es usada para obtener un caracter del teclado
char get_char (void);  


// get_mask : Esta funcion crea la mascara que ingresa el usuario
//
// - char * string : Es un puntero a un arreglo (de 9 0 17 elementos) de char QUE DEBE VENIR INICIALIZADO CON '0' 
// - int max_bits  : Es el numero maximo de bits de registro al que se le aplica la mascara (8 o 16)
void get_mask (char * string, int max_bits);


// print_status : Esta funcion imprime bit a bit un registro de 8 bits
// - void * point : es un puntero a void que apunta a una estructura (bitfield) de 8 bits 
// - char puerto : Indica que puerto se va a imprimir ('a', 'b' o 'd')

void print_status (void * point, char puerto);

// toggle_print : Es una funcion que hace parpadear a un puerto
// - void * point : Es un puntero que contiene al puerto a imprimir
// - int repeat : Indica cuantas veces se va a repetir

void toggle_print (void * pointer2, int repeat);

/*
 * Library: nonblock
 * This library allows non blocking reading from stdin on Linux systems.
 * Author: Clementina Calvo
 * Date: 05/2016
 *
 * Heavily based on this blog post: http://cc.byexamples.com/2007/04/08/non-blocking-user-input-in-loop-without-ncurses/
 */

typedef enum {NB_ENABLE, NB_DISABLE} nb_State;

/* void kbhit(void)
 * This function performs non-blocking checking on the standard input (stdin)
 * Input: -
 * Output: non-zero if there's user input on stdin, else zero.
 *
 * Warning: When in canonical mode, input won't be retrieved unless user hits 'enter'
 * afterwards.
 */

int kbhit(void);

/* Due to the canonical mode of your terminal, enter needs to be hit to confirm user input. 
 * Canonical mode means it always waits for enter to confirm the user input. 
 * If that is not your case, bellow is another function to cater that.
 *
 * void nonblock(nb_State state)
 * This functions enables/disables canonical mode on stdin.
 * Input: nb_State state, the desired action.
 * Output: -
 *
 * For more info on canonical mode: http://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html
 */
void nonblock(nb_State state);


/* General usage:
 *
 * ...
 * 
 * nonblock(NB_ENABLE)	//enable non-blocking
 * while(!kbhit()) {
   	//do stuff
   }
 * // user input
 * nonblock(NB_DISABLE)	//return back to normal
 *
 * ...
 */

 #endif 
 // _INPUT_OUTPUT_H_