
#include <stdio.h>
#include "operations.h"
#include "validation.h"
#include "input_output.h"
#include "struct.h"



#define PORTA ('a')
#define PORTB ('b')
#define PORTD ('d')

#define ACTUAL_STATUS ('0')
#define BITSET ('1')
#define BITCLR ('2')
#define BITGET ('3')
#define BITTOGGLE ('4')
#define MASKON ('5')
#define MASKOFF ('6')
#define MASKTOGGLE ('7')
#define INTERMITENCE ('b')
#define ALLOFF ('c')
#define ALLON ('s')
#define ENDOFPROGAM 27

#define NOERRORS (0)
#define ERROR_MASK (1)


int main (void)
{
	char option = 'p', bit_modify, port;
	int option_validation = TRUE, status,move_screen;	

	void (*funcion) (char puerto , int bit , void * pointer2);
	void * pointer; 
	port_16_t portd;
	portd.full_reg= 0;
	
	char * mask_array;
	char short_array[9] = {"00000000"};
	char long_array[17] = {"0000000000000000"} ;
	int max_bits, i ,mask_error = NOERRORS;
	
	pointer = &(portd.half_reg.porta.eight_reg);
	printf("\nEstado inicial puerto A: ");
	print_status(pointer , PORTA);
	printf("\n");
	pointer = &(portd.half_reg.portb.eight_reg);
	printf("\nEstado inicial puerto B: ");
	print_status(pointer , PORTB);
	printf("\n");

	while ( ( option != ENDOFPROGAM ) && ( bit_modify != ENDOFPROGAM ) && ( port != ENDOFPROGAM ))
	{
		printf("\nPor favor ingrese la operación que desee realizar:\n");
		printf("%c para imprimir en pantalla el esta actual de los leds\n", ACTUAL_STATUS);	
		printf("%c para encender un led apagado\n", BITSET);
		printf("%c para apagar un led encendido\n", BITCLR);
		printf("%c para verificar el estado de un led\n", BITGET);
		printf("%c para invertir el estado de un led\n", BITTOGGLE);
		printf("%c para ingresar una máscara para el encendido de leds\n", MASKON);
		printf("%c para ingresar una máscara para el apagado de leds\n", MASKOFF);
		printf("%c para ingresar una máscara para invertir el estado de los led\n", MASKTOGGLE);
		printf("%c para que los led parpadeen\n", INTERMITENCE);
		printf("%c para apagar todos los led\n", ALLOFF);
		printf("%c para encender todos los led\n", ALLON);
		printf("la tecla ESC para finalizar el programa\n");

		do
		{																			//SELECCION DEL USUARIO PARA OPERACION
			option = get_char();
			
			option_validation = op_valid(option);

			if (option_validation == FALSE)
			{
				printf("\nHa ingresado una opción incorrecta, reingrese por favor: \n");
			}
		} while (option_validation == FALSE);

		switch (option)											//SE ASIGNAN LOS PUNTEROS A FUNCION PARA OPERAR CON MASCARAS
		{
			case MASKON: funcion = &bitset; break;
			case MASKOFF: funcion = &bitclr; break;
			case MASKTOGGLE: funcion = &bittoggle; break;
		}

		
		if ( (option == BITSET)||(option == BITCLR)||(option == BITGET)||(option == BITTOGGLE) )	// para modificaciones de bits 
		{
			printf ("\nIngrese el puerto en el que desea operar\n");
			do
			{
				port = get_char();
				switch (port)
				{
					case 'A' : port = PORTA ; break ;
					case 'B' : port = PORTB ; break ;
					case 'D' : port = PORTD ; break ;
				}
				if ( (port != PORTA )&&(port != PORTB) )
				{
					printf("\nIngresó un puerto no válido\n");
				}
			} while ( (port != PORTA )&&(port != PORTB ) );	

			printf ("\nIngrese el bit que desea modificar\n");
			do
			{
				bit_modify = get_char();
				if ( (bit_modify < '0')||(bit_modify > '7') )
				{
					printf("\nIngreso no válido\n");
				}
			} while ( (bit_modify < '0')||(bit_modify > '7') );
			
			printf ("\nport %c , bit %c\n", port, bit_modify);

			pointer = &(portd.half_reg);

			bit_modify = bit_modify - '0';
			
			switch (option)
			{
				case BITSET: bitset (port , (int) bit_modify, pointer); break;
				case BITCLR: bitclr (port , (int) bit_modify,  pointer); break;
				case BITGET: status = bitget (port, (int) bit_modify, pointer); break;
				case BITTOGGLE: bittoggle (port , (int) bit_modify, pointer); break;
			}
		}

		else if ( (option == MASKON)||(option == MASKOFF)||(option == MASKTOGGLE) ) 	// para modificaciones con mascaras
		{
			printf ("\nIngrese el puerto en el que desea operar\n");
			do
			{
				port = get_char();

				switch (port)
				{
					case 'A' : port = PORTA ; break ;
					case 'B' : port = PORTB ; break ;
					case 'D' : port = PORTD ; break ;
				}
				if ( (port != PORTA )&&(port != PORTB)&&(port != PORTD ) )
				{
					printf("\nIngresó un puerto no válido\n");
				}
			} while ( (port != PORTA )&&(port != PORTB )&&(port != PORTD ) );

			if (port != PORTD)
			{
				mask_array = short_array;
				max_bits = 8;

				pointer = &(portd.half_reg);
			}
			else
			{
				mask_array = long_array;
				max_bits = 16;
				pointer = &(portd.half_reg);			//////////////////////
			}

			printf ("\nIngrese la máscara con la que desee operar\n");
			do 
			{
				get_mask (mask_array , max_bits );
				for (i=0 ; i < max_bits ; ++i)
				{
					if (i == 0)
					{
						mask_error = NOERRORS;
					}
					if ((*(mask_array + i) != '0') && (*(mask_array + i) != '1'))
					{
						mask_error = ERROR_MASK;

					}
				}
				if (mask_error == ERROR_MASK)
				{
					printf("\nHa ingresado de forma incorrecta la máscara, solo puede ingresar ceros y unos\n");
				}
			} while (mask_error == ERROR_MASK);	

			mask_8bits (port , mask_array, pointer, funcion ) ;

			for ( i = 0 ; i < max_bits -1 ; ++i)
			{
				*(mask_array + i) = '0';
			}

			*(mask_array + i) = 0;

		}

		else if (option == ALLON)
		{
			portd.full_reg= 0xffff;
		}
		else if (option == ALLOFF)
		{
			portd.full_reg= 0;
		}
		else if (option == INTERMITENCE)
		{

			toggle_print (&(portd.half_reg), 6);
		}
		else if (option == ACTUAL_STATUS)
		{
			for (move_screen = 0 ; move_screen < 50 ; ++move_screen)
			{
				putchar('\n');
			}
			pointer = &(portd.half_reg.porta.eight_reg);
			printf("\nEstado actual puerto A: ");
			print_status(pointer , PORTA);
			printf("\n");
			pointer = &(portd.half_reg.portb.eight_reg);
			printf("\nEstado actual puerto B: ");
			print_status(pointer , PORTB);
			printf("\n");
		}


		if (option != ACTUAL_STATUS)
		{
			for (move_screen = 0 ; move_screen < 50 ; ++move_screen)
			{
				putchar('\n');
			}
			if (option == BITGET)
			{ 
				printf("\nbit %d = %d\n",(int) bit_modify, ( status ? 1 : 0) );
			}

			pointer = &(portd.half_reg.porta.eight_reg);
			printf("\nEstado actual puerto A: ");
			print_status(pointer , PORTA);
			printf("\n");
			pointer = &(portd.half_reg.portb.eight_reg);
			printf("\nEstado actual puerto B: ");
			print_status(pointer , PORTB);
			printf("\n");
		}
	}	
	
	
		pointer = &(portd.half_reg.porta.eight_reg);
		printf("\nEstado final puerto A: ");
		print_status(pointer , PORTA);
		printf("\n");
		pointer = &(portd.half_reg.portb.eight_reg);	
		printf("\nEstado final puerto B: ");
		print_status(pointer , PORTB);
		printf("\n");


	return 0;
}
