
#include <stdio.h>
#include <unistd.h>
#include "operations.h"
#include "operationsdefine.h"
#include "validation.h"
#include "input_output.h"
#include "struct.h"
#include "R_pin.h"


#define PORTA ('a')
#define NOERRORS (1)

#define PORT_LENGTH (8)
#define INITSTATE ('0')
#define STARTOPTIONNULL ('p')

int main (void)
{
	char option = STARTOPTIONNULL, port = PORTA;
	int option_validation = TRUE, counter;	
	void * pointer; 	

	void (*funcion) (char puerto , int bit , void * pointer2); 
	port_16_t portd;

	char * mask_array;
	char short_array[9] = {"00000000"};
        char all_one[8] = {"1111111"};
	int max_bits, i ,mask_error = NOERRORS;

	//Inicialización

	portd.full_reg= INITSTATE - 0;			//inicializacion de la estructura que acompaña a los leds	
	set_leds(&(portd.half_reg.porta.eight_reg));	//Seteo de pines para el uso de la Ras pi


	while ( ( option != ENDOFPROGRAM ) && ( port != ENDOFPROGRAM ))
	{
		printf("\nPor favor ingrese la operación que desee realizar:\n");
		printf("los numeros del 1 al 7 para prender o apagar los leds\n");	//modicado
		printf("%c para ingresar una máscara para el encendido de leds\n", MASKON);
		printf("%c para ingresar una máscara para el apagado de leds\n", MASKOFF);
		printf("%c para ingresar una máscara para invertir el estado de los led\n", MASKTOGGLE);
		printf("%c para que los led parpadeen\n", INTERMITENCE);
		printf("%c para apagar todos los led\n", ALLOFF);
		printf("%c para encender todos los led\n", ALLON);
		printf("la tecla ESC para finalizar el programa\n");

		do						//SELECCION DEL USUARIO PARA OPERACION
		{		
			option = get_char();
			option_validation = op_valid(option);

			if (!option_validation)
			{
				printf("\nHa ingresado una opción incorrecta, reingrese por favor: \n");
			}
		} while (option_validation == FALSE);

		switch (option)						//SE ASIGNAN LOS PUNTEROS A FUNCION PARA OPERAR CON MASCARAS
		{
			case MASKON: funcion = &bitset; break;
			case MASKOFF: funcion = &bitclr; break;
			case MASKTOGGLE: funcion = &bittoggle; break;
		}
		
		if ( (option >='0') && (option <='7') )	// para modificaciones de bits 
		{
                    pointer = &(portd.half_reg);
                    bittoggle (port , (int) (option - '0') , pointer); 
		}

		else if ( (option == MASKON)||(option == MASKOFF)||(option == MASKTOGGLE) ) 	// para modificaciones con mascaras
		{
				mask_array = short_array;
				max_bits = PORT_LENGTH;
				pointer = &(portd.half_reg);

			printf ("\nIngrese la máscara con la que desee operar\n");
			do 
			{
				mask_error = FALSE;
				get_mask (mask_array , max_bits );
				mask_error = check_mask (mask_array, max_bits);

				if (!mask_error)
				{
					printf("\nHa ingresado de forma incorrecta la máscara, solo puede ingresar ceros y unos\n");
				}
			} while (!mask_error);	

			mask_bits (port , mask_array, pointer, funcion ) ;

			for ( i = 0 ; i < max_bits-1 ; ++i)
			{
				*(mask_array + i) = '0';
			}

			*(mask_array + i) = 0;
		}

		else if ((option == ALLON) || (option == ALLOFF))
		{
                    switch (option)
                    {
                        case ALLOFF : funcion = bitclr; break;
                        case ALLON : funcion = bitset; break;
                    }
                    
                    mask_bits(port,all_one,&(portd.half_reg), funcion);
                    set_leds(&(portd.half_reg.porta.eight_reg));

		}

		else if (option == INTERMITENCE)
		{
			for ( counter = 0; counter < 10 ; ++counter)
			{
				funcion = bittoggle;
				mask_bits(PORTA,all_one,&(portd.half_reg), funcion);
                   		set_leds(&(portd.half_reg.porta.eight_reg));
				sleep(1);
			}
			//toggle_print (&(portd.half_reg.porta), 6);
		}
		putchar('\n');
		putchar('\n');
	}

	unset_leds();
	portd.full_reg= INITSTATE - 0; 		//Para dejar la estructura en el estado incial
	
	return 0;
}
