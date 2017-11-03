#include "get_char.h"
#include "nonblock.h"


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