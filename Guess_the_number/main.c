#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "get_char.h"
#include "nonblock.h"


#define MAX_NUM 9
#define MAX_TIME 5
#define PI 3.14159265359
 
int main ()
{
	    //MANEJO DEL TIEMPO
            unsigned int x_seconds=0;   
            unsigned int x_milliseconds=0;
            unsigned int time_in_secs=0;
            // VARIABLES UTILES
            int safe_print=10;  //Asegura que no se imprima muchas veces el mensaje del tiempo

            //VARIABLES  DE JUEGO
        
        
             //MENSAJES
            char* msg_time_left="Te quedan ";
        
            
            int abort=0; int touched=0;
            clock_t x_startTime,x_countTime;     
            time_in_secs=MAX_TIME; 
            x_startTime=clock();  // comienza reloj
            
            nonblock(NB_ENABLE);
            while (!abort) 
                {
                        x_countTime = clock();    //actualizo el timer
                        x_milliseconds=x_countTime-x_startTime;
                        x_seconds=(x_milliseconds/(CLOCKS_PER_SEC));

                      

                        if (!(x_seconds%1))
                        {
                            if (!(x_seconds==safe_print))
                            {
                            safe_print=x_seconds;
                            printf("\n%s: %ud s\n",msg_time_left, x_seconds);
                            }
                        }
                        if (kbhit())
                        {
                            abort=1;
                        }
                        
                }
                printf( "\nPUTO\n");
    
return 0;
}