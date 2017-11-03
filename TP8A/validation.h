#ifndef _validation_
#define _validation_

#define ON (1)
#define OFF (0)
#define TRUE (1)
#define FALSE (0)

// valid_string    		: Esta funion valida un string para que solo sea una mascara, de ser invalido
//					 devolvera un 0.
// - char * string 		: Es un string de char que debe ser la mascara que se quiere aplicar
//  int valid_string (char * string);

// valid_char	   		: Esta funcion valida un char indivudual y devuelve un cero si no es valido
//
// - char input			: Es el char que se quiere validar
// - char verification  : Es lo que el "input" debe ser para que sea valido.
//  int valid_char (char input, char verification);


int op_valid (char input);
#endif