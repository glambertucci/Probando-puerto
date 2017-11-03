#include "operations.h"

#define INVERT(a) (7-a)		// Permite invertir el contador para poder ver la posicion del
#define ON (1)
#define OFF (0)


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
		case 0 : port->b0 = ON; break;						//bit 0
		case 1 : port->b1 = ON; break;
		case 2 : port->b2 = ON; break;
		case 3 : port->b3 = ON; break;
		case 4 : port->b4 = ON; break;
		case 5 : port->b5 = ON; break;
		case 6 : port->b6 = ON; break;
		case 7 : port->b7 = ON; break;						//bit 7
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
		case 0 : port->b0 = OFF; break;						//bit 0
		case 1 : port->b1 = OFF; break;
		case 2 : port->b2 = OFF; break;
		case 3 : port->b3 = OFF; break;
		case 4 : port->b4 = OFF; break;
		case 5 : port->b5 = OFF; break;
		case 6 : port->b6 = OFF; break;
		case 7 : port->b7 = OFF; break;						//bit 7
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
		case 0 : result = port->b0 ; break;					//bit 0
		case 1 : result = port->b1 ; break;
		case 2 : result = port->b2 ; break;
		case 3 : result = port->b3 ; break;
		case 4 : result = port->b4 ; break;
		case 5 : result = port->b5 ; break;
		case 6 : result = port->b6 ; break;
		case 7 : result = port->b7 ; break;					//bit 7
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
		case 0 : ( port->b0 ? ( port->b0 = OFF ) : ( port->b0 = ON ) ) ; break;
		case 1 : ( port->b1 ? ( port->b1 = OFF ) : ( port->b1 = ON ) ) ; break;
		case 2 : ( port->b2 ? ( port->b2 = OFF ) : ( port->b2 = ON ) ) ; break;
		case 3 : ( port->b3 ? ( port->b3 = OFF ) : ( port->b3 = ON ) ) ; break;
		case 4 : ( port->b4 ? ( port->b4 = OFF ) : ( port->b4 = ON ) ) ; break;
		case 5 : ( port->b5 ? ( port->b5 = OFF ) : ( port->b5 = ON ) ) ; break;
		case 6 : ( port->b6 ? ( port->b6 = OFF ) : ( port->b6 = ON ) ) ; break;
		case 7 : ( port->b7 ? ( port->b7 = OFF ) : ( port->b7 = ON ) ) ; break;
	}
}


void mask_8bits (char puerto, char * array, void * pointer2, void (*funcion) (char puerto, int bit, void * pointer2))
{
	int counter;

	void * pointer;
	b16_t * aa = pointer2;


	for (counter = 0 ;  ( *(array + counter) != 0 ) || (counter < 8) ; ++counter)		
	{
		if ( *(array + counter) == '1')
		{
			(*funcion ) (puerto,INVERT(counter),pointer2);
		}
	}
}



/* Esta funcion esta comenteada para su proxima implementacion 
void port_d_func (b16_t * pointer, int bit, void (*funcion) (char puerto, int bit, b16_t * pointer) )
{
	b1_t * port_a = &(pointer->porta.eight_reg);
	b1_t * port_b = &(pointer->portb.eight_reg);

	int puerto;

	if ( bit >= 8)
	{
		puerto = 'a';
		bit = bit - 8;
		(*funcion) (puerto, bit, pointer);

	}
	else
	{
		puerto = 'a';
		(*funcion) (puerto, bit, pointer);
	}
}*/