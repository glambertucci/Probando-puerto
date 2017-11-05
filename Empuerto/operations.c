#include "operations.h"

void blink_all(void * element_pointer, void * background,void * led_on_void, void * led_off_void,int elementos, int repetir, ALLEGRO_EVENT_QUEUE * event_line)
{
    int counter;
    element * elemento = element_pointer;
    
            // VARIABLES UTILES
            int safe_print=10;  //Asegura que no se imprima muchas veces el mensaje del tiempo           
            int abort=false;
            //COSAS DE TIMER
            clock_t x_startTime,x_countTime;     
            x_startTime=clock();  // comienza reloj
            int  x_seconds=0;   
            int x_milliseconds=0;
           
            while (!abort) 
                {
                    ALLEGRO_EVENT event;
                    if(al_get_next_event(event_line,&event))
                    {
                        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
                        {
                            abort = true ;
                        }    
                    } 
                   
                    x_countTime = clock();    //actualizo el timer
                    x_milliseconds=x_countTime-x_startTime;
                    x_seconds=(x_milliseconds/(CLOCKS_PER_SEC));

                      

                        if (!((x_seconds*2)%1)) //es multiplicado por dos para que titile dos veces por segundo
                        {
                            if (!(x_seconds==safe_print))	
                            {
                            	safe_print=x_seconds;
                            	for (counter = 0 ;counter < elementos; ++ counter)
                                {
                                    bit_switch(elemento + counter);
                                }
                                print_display(element_pointer,(void *) background,led_on_void,led_off_void, 11);
                            }
                        }

                }
 

}
void set_all( void * element_pointer, int elementos)
{
    element * elemento = element_pointer;
    int counter;
    
    for (counter = 0 ;counter < elementos; ++ counter)
    {
        (elemento + counter)->led_on = true;
    }
}

void clr_all( void * element_pointer, int elementos)
{
    int counter;
    element * elemento = element_pointer;
    
    for (counter = 0 ;counter < elementos; ++ counter)
    {
        (elemento + counter)->led_on = false;
    }
}


void bit_switch (void * element_pointer)
{
    element * elemento = element_pointer;
  
    if (elemento->led_on)
    {
        elemento->led_on = false;
    }
       else if (!elemento->led_on)
    {
       elemento->led_on = true;
	
    }
}

#define SQUARE_X(counter) (ESPACIO_LAT+(counter * ESPACIO_INT) + (counter * LARGO_X ))
#define RECTANGLE_X(counter) (ESPACIO_LAT_RECT + (counter * ESPACIO_INT_RECT) + (counter *LARGO_RECT_X))


void init_coord (void * element_pointer ,bool led_on ,bool led_enabled,void * bitmap_pointer)
{
    element * elemento = element_pointer;
    ALLEGRO_BITMAP * bitmap = bitmap_pointer;
    static int counter1 = 0;
    static int counter2 = 0;
    
    elemento->led_enabled = led_enabled;

    if (elemento->led_enabled)                          // Si es un led
    {
        elemento->position_x = SQUARE_X(counter1); 
        elemento->position_y = 100;
        elemento->lenght_x= LARGO_X;
        elemento->lenght_y= LARGO_Y;
        ++counter1;
    }
    else if (!(elemento->led_enabled))                  // Si es un boton
    {
        elemento->position_x = RECTANGLE_X(counter2); 
        elemento->position_y = 400;
        elemento->lenght_x= LARGO_RECT_X;
        elemento->lenght_y= LARGO_RECT_Y;
        ++counter2;
    }
    elemento->led_on = led_on;
    elemento->bitmap = bitmap;
  
}
