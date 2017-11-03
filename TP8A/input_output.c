#include <stdio.h>					//librerias estandar que utilizan todas las
#include <unistd.h>					// funciones
#include "input_output.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char get_char(void)
{
	char tecla;
	nonblock(NB_ENABLE);	//enable non-blocking
	while(!kbhit()) 
	{
	//do stuff
	}
	tecla = getchar();// user input
	nonblock(NB_DISABLE);	//return back to normal
	return tecla;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int LetterCounter ( char * point, char terminador_a, char terminador_b);	

void get_mask (char * string_return, int max_bits)
{
	int counter, counter_return, leave = 0, tecla, lenght;

	char string_short [ 9 ]  = {1,1,1,1,1,1,1,1,0} ; 
	char string_long [ 17 ]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}; 

	char * string; 

	switch (max_bits)
	{
		case 8 : string = string_short ; break ;
		case 16 : string = string_long ; break ;
	}

	for (counter = 0 ; ( *(string + counter) != 0 ) && ( leave == 0) ; ++ counter)	// copia lo que se ingresa a un string temporal
	{
		if (  ( (tecla = getchar()) != '\n' ) )
		{ 	
			*(string + counter) = tecla;
		}
		else
		{
			leave = 1;
		}
	}

	lenght = LetterCounter(string , 1,0);

	for (counter_return = ( max_bits - lenght ) , counter = 0 ;  ( *(string + counter) != 0 ) ; ++counter_return, ++ counter)
	{ 	
		if ( *(string + counter) == '1' )
		{ 
			*(string_return + counter_return) = '1';
		}
	}

}

static int LetterCounter ( char * point, char terminador_a, char terminador_b)								
{
	int letter;
	
	for ( letter = 0 ; ( *(point + letter) != terminador_a ) && ( *(point + letter) != terminador_b ) ; ++letter )
	{	
	}
	return letter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_status (void * point, char puerto)
{
	b1_t * point_struct = (b1_t *) point;		//Castea el puntero a void a un bitfield

	putchar( ( point_struct->b7 ? LEDON : LEDOFF ) );	//Imprime el bit mas significativo
	putchar( ( point_struct->b6 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b5 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b4 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b3 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b2 ? LEDON : LEDOFF ) );
	putchar( ( point_struct->b1 ? LEDON : LEDOFF ) );			
	putchar( ( point_struct->b0 ? LEDON : LEDOFF ) );	//Imprime el bit menos significativo
	
	if (puerto != 'd')
	{
		putchar('\n');
	}
}

#define PORTA1 'a'
#define PORTB1 'b'

void toggle_print (void * pointer2, int repeat)
{
	int counter_enter, counter_repeat;
	b16_t * pointer = pointer2;
	b1_t * point;
	char array[9] = "11111111";
	void (*funcion) (char puerto, int bit, void * pointer2);

	funcion = bittoggle;

	if (repeat % 2 != 0)
	{
		++repeat;
	}

	for ( counter_repeat = 0 ; counter_repeat < repeat ; ++counter_repeat)
	{ 

		for (counter_enter = 0 ; counter_enter < 50 ; ++counter_enter)
		{
			putchar('\n');
		}

		point = &(pointer->porta.eight_reg);

		printf("\nEstado actual puerto A: ");
		print_status( point , PORTA1 );

		point = &(pointer->portb.eight_reg)	;

		printf("\nEstado actual puerto B: ");
		print_status( point , PORTB1 );			

		sleep(1);

		mask_8bits (PORTA1, array, pointer, funcion);
		mask_8bits (PORTB1, array, pointer, funcion);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <time.h>						// Librerias estandar que solo utilizan las proximas funciones
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#ifdef _WIN32
   #error "This program is only targeted at Linux systems"
#endif



void nonblock(nb_State state) {
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state==NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int kbhit(void) {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}



int _test() {
    char c;
    int i=0;

    nonblock(NB_ENABLE);
    while(!i)
    {
        usleep(1);
        i=kbhit();
        if (i!=0)
        {
            c=fgetc(stdin);
            if (c=='q')
                i=1;
            else
                i=0;
        }

        fprintf(stderr,"%d ",i);
    }
    printf("\n you hit %c. \n",c);
    nonblock(NB_DISABLE);


    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

