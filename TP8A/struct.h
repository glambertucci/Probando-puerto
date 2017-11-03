#ifndef _struct_
#define _struct_

typedef struct 			// Un puerto de 8 bits visto bit a bit
{
	char b0 :1;
	char b1 :1;
	char b2 :1;
	char b3 :1;
	char b4 :1;
	char b5 :1;
	char b6 :1;
	char b7 :1;

} b1_t;


typedef union			// Union de las dos formas de ver a un registro de 8 bits
{
	char  full_reg;
	b1_t  eight_reg;

}port_8_t;

typedef struct 				// Un puerto de 16 bits visto de a 8 bits
{
	port_8_t portb ;
	port_8_t porta ;

} b16_t;

typedef union				// Union de las formas de mostrar un registro de 16 bits
{
	int full_reg :16;
	b16_t half_reg;

} port_16_t;

#endif