#ifndef _operations_
#define _operations_

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "input_output.h"
#include "R_pin.h"

// funcion bittoggle : Esta funcion invierte el estado de un bit de un registro
//
// - char puerto 	 : Indica que registro se debe modificar ('a' o 'b')
// - int bit 		 : Indica que bit debe ser modificado (0-7)
// - void * pointer2 : Es un puntero que apunta a estructura que contiene los puertos A y B (el tipo de datos debe ser b16_t *)
void bittoggle (char puerto, int bit, void * pointer2);

//funcion mask_8bits : Realiza las operaciones de bitset, bitclear y bittoggle a un puerto utilizando una mascara.
//
// char puerto : Es el puerto sobre el que se va a realizar la operacion ('a' o 'b'). Solo de 8bits
// char * array : Es el arreglo que contiene a la mascara, debe tener 9 elementos (8 numeros y el terminador) que solo pueden estar seteados en '1' y '0'
// void * pointer :Es un puntero a void que apunta a una estructura que contiene a los puertos A y B (el tipo de datos debe ser b16_t *)
// void (*funcion) (char puerto, int bit, void * pointer2)) : Es un puntero a funcion (bitset, bitclr o bittoggle)
void mask_bits (char puerto, char * array, void * pointer, void (*funcion) (char puerto, int bit, void * pointer2));


// funcion bitset : Esta funcion prende un bit de un registro
//
// - char puerto 	 : Indica que registro se debe modificar ('a' o 'b')
// - int bit 		 : Indica que bit debe ser modificado (0-7)
// - void * pointer2 : Es un puntero que apunta a estructura que contiene los puertos A y B (el tipo de datos debe ser b16_t *)
void bitset (char puerto, int bit, void * pointer2);

// funcion bitclr : Esta funcion apagar un bit de un registro
//
// - char puerto 	 : Indica que registro se debe modificar ('a' o 'b')
// - int bit 		 : Indica que bit debe ser modificado (0-7)
// - void * pointer2 : Es un puntero que apunta a estructura que contiene los puertos A y B (el tipo de datos debe ser b16_t *)
void bitclr (char puerto, int bit, void * pointer2);

// funcion bitget : Esta funcion devuelve el valor de 1 bit de cualquier bit de un registro
//
// char puerto : Es el puerto sobre el que se va a realizar la operacion ('a' o 'b'). Solo de 8bits
// int bit : Es el bit del cual se quiere conocer el valor (0-7)
// void *pointer2 : Es un puntero a void que apunta a una estructura que contiene a los puertos A y B (el tipo de datos debe ser b16_t *)
int bitget (char puerto, int bit, void * pointer2);

#endif
