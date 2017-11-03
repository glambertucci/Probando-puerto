#include "operations.h"

#define INVERT(a) (7-a)		// Permite invertir el contador para poder ver la posicion del
#define ON (1)
#define OFF (0)
#define LED_ON ('1')		//Para Raspberry pi
#define LED_OFF ('0')		//Para Raspberry pi

void bitset (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg); break;
		case 'b' : port = &(pointer->portb.eight_reg); break;
	}
	switch (bit)
	{
		case 1 : port->b0 = ON; state_set (LED_1, LED_ON); break;	//bit 0
		case 2 : port->b1 = ON; state_set (LED_2, LED_ON); break;
		case 3 : port->b2 = ON; state_set (LED_3, LED_ON); break;
		case 4 : port->b3 = ON; state_set (LED_4, LED_ON); break;
		case 5 : port->b4 = ON; state_set (LED_5, LED_ON); break;
		case 6 : port->b5 = ON; state_set (LED_6, LED_ON); break;
		case 7 : port->b6 = ON; state_set (LED_7, LED_ON); break;			
		case 8 : port->b7 = ON; break;					//bit 7
	}
}

void bitclr (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg); break;
		case 'b' : port = &(pointer->portb.eight_reg); break;
	}

	switch (bit)
	{
		case 1 : port->b0 = OFF; state_set (LED_1, LED_OFF); break;	// bit 0 Led 0
		case 2 : port->b1 = OFF; state_set (LED_2, LED_OFF); break;
		case 3 : port->b2 = OFF; state_set (LED_3, LED_OFF); break;
		case 4 : port->b3 = OFF; state_set (LED_4, LED_OFF); break;
		case 5 : port->b4 = OFF; state_set (LED_5, LED_OFF); break;
		case 6 : port->b5 = OFF; state_set (LED_6, LED_OFF); break;
		case 7 : port->b6 = OFF; state_set (LED_7, LED_OFF); break;
		case 8 : port->b7 = OFF; break;					
	}
}

int bitget (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;
	int result;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg);
		case 'b' : port = &(pointer->portb.eight_reg);
	}

	switch (bit)
	{
		case 1 : result = port->b0 ; break;					//bit 0
		case 2 : result = port->b1 ; break;
		case 3 : result = port->b2 ; break;
		case 4 : result = port->b3 ; break;
		case 5 : result = port->b4 ; break;
		case 6 : result = port->b5 ; break;
		case 7 : result = port->b6 ; break;
		case 8 : result = port->b7 ; break;					//bit 7
	}

	return result;
}

void bittoggle (char puerto, int bit, void * pointer2)
{
	b1_t * port;
	b16_t * pointer = pointer2;

	switch (puerto)
	{
		case 'a' : port = &(pointer->porta.eight_reg); break;
		case 'b' : port = &(pointer->portb.eight_reg); break;
	}

	switch (bit)
	{
            case 1: ((port->b0) ? (port->b0 = OFF) : (port->b0 = ON)) ; state_set (LED_1, port->b0 + '0'); break;
            case 2: ((port->b1) ? (port->b1 = OFF) : (port->b1 = ON)) ; state_set (LED_2, port->b1 + '0'); break;
            case 3: ((port->b2) ? (port->b2 = OFF) : (port->b2 = ON)) ; state_set (LED_3, port->b2 + '0'); break;
            case 4: ((port->b3) ? (port->b3 = OFF) : (port->b3 = ON)) ; state_set (LED_4, port->b3 + '0'); break;
            case 5: ((port->b4) ? (port->b4 = OFF) : (port->b4 = ON)) ; state_set (LED_5, port->b4 + '0'); break;
            case 6: ((port->b5) ? (port->b5 = OFF) : (port->b5 = ON)) ; state_set (LED_6, port->b5 + '0'); break;
            case 7: ((port->b6) ? (port->b6 = OFF) : (port->b6 = ON)) ; state_set (LED_7, port->b6 + '0'); break;
	}
}


void mask_bits (char puerto, char * array, void * pointer2, void (*funcion) (char puerto, int bit, void * pointer2))
{
	int counter;

	for (counter = 0 ;  ( *(array + counter) != 0 ) || (counter < 8) ; ++counter)		
	{
		if ( *(array + counter) == '1')
		{
			(*funcion ) (puerto,INVERT(counter),pointer2);
		}
	}
}


