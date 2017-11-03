#ifndef _validation_
#define _validation_

#include "operationsdefine.h"

#define ON (1)
#define OFF (0)
#define TRUE (1)
#define FALSE (0)

// esta funcion valida los caracteres individuales que son ingresados por el usuario, para las operaciones.
//
// char input : Es el caracter ingresado
int op_valid (char input);

// Esta funcion se fija que para la mascara solo se ingresen 1s y 0s.
//
// char * mask_array : Es un arreglo que se le envia a la funcion para que copie en el la mascara que ingresa el usuario. 
//		       Debe ser de 8 elementos mas uno para el terminador.
// int max_bits : Es el largo maximo de la mascara
int check_mask (char * mask_array, int max_bits);


#endif	//_validation_
