#include "print_status.h"
#include "struct.h"
#include "operations.h"
#include "get_mask.h"
void cut_string (char * main_string, char * mini_string);

int main (void)
{ 
	port_16_t portd;

	char array[9] = "11111111";		// Estos arreglos son para probar las funciones de mascaras
	char array2[9] = "00000000";


	void (*funcion) (char puerto, int bit, void * pointer2);

	void * bport = &portd.half_reg.portb.eight_reg;
	void * aport = &portd.half_reg.porta.eight_reg;
	void * pip = &portd.half_reg;

	char puerto = 'a';


	portd.full_reg= 0;



	bitset (puerto , 0, pip);

	bitset (puerto, 2, pip);

	bittoggle (puerto, 1 , pip);

	bitset (puerto, 5, pip);


/*
	printf("prueba funarray2ciones bit... = ");
	
	print_status(bport,'a');
////////////////////////////////////////////////////////////////
	funcion = bittoggle;

	mask_8bits (puerto, array, pip, funcion);

	printf("prueba masktoggle... = ");

	print_status(bport,'a'); 
	////////////////////////////////////////////////////////////////
	funcion = bitclr;

	char puerto = 'b';

	mask_8bits (puerto, array, pip, funcion);

	printf("prueba maskoff... = ");

	print_status(bport,'a');  
////////////////////////////////////////////////////////////////
	funcion = bitset;

	 puerto = 'b';

	get_mask(array2, 8);

	mask_8bits (puerto, array2, pip, funcion);

	printf("prueba maskon... = ");

	print_status(bport,'a');

////////////////////////////////////////////////////////////////	
//			ASI TIENEN QUE FUNCIONAR LAS OPERACIONES CON EL REGISTRO D

	char array3[17] = "1110101010101000";
	char mini_string [9];


	funcion = bittoggle;

	puerto = 'a';

	printf("modificando reg A\n");

	mask_8bits (puerto, array3, pip, funcion);

	printf("modificando reg B\n");

	cut_string(array3, mini_string);

	//printf("mini_pointer main%s\n", mini_string);

	puerto = 'b';

	mask_8bits (puerto, mini_string, pip, funcion);

	*/
//////////////////////////////////////////////////////////////////
//	ASI SE APLICAN LAS FUNCIONES QUE TRABAJAN DE A UN BIT EN EL REGISTRO D
/*	funcion = bitset;	

	port_d_func (pip, 15, funcion );*/


////////////////////////////////////////////////////////////////////
//	ASI SE IMPRIME EL REGISTRO D
	printf("prueba imprimir D... = \n");
	
	printf("Registro A =");
	print_status(aport,'a');

	printf("Registro B =");
	print_status(bport,'b');

	putchar('\n');
	/*

	int mask_error = 0,  i;
	#define ERROR_MASK max_bits(1)

	do 
	{
		get_mask (array2 , 8 );

		for (i=0 ; i < 8 ; ++i)
		{
			if ((*(array2 + i) != '0') && (*(array2 + i) != '1'))
			{
				mask_error = ERROR_MASK;

			}
		}
		if (mask_error == ERROR_MASK)
		{
			printf("\nHa ingresado de forma incorrecta la máscara, solo puede ingresar ceros y unos\n");
		}
	} while (mask_error == ERROR_MASK);	

	printf("Mask = %s\n", array2);*/



	return 0;
}

void cut_string (char * main_string, char * mini_string)
{

	//printf("main_string ANTES = %s\n", main_string);

	int counter ;

	for (counter = 0 ; counter <8 ; ++counter )
	{
		*(mini_string + counter) = *(main_string + 8 + counter);
	}

	*(mini_string + counter) = 0;

	//printf("main_string = %s\n", main_string);

	//printf("mini_string =%s\n", mini_string);

}

