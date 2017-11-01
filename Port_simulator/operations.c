#include "operations.h"

void blink_all(void * element_pointer, void * background,void * led_on_void, void * led_off_void,int elementos, int repetir)
{
    int counter, count_repeat;
    element * elemento = element_pointer;
    ALLEGRO_BITMAP * led_on = led_on_void;
    ALLEGRO_BITMAP * led_off = led_off_void;
    
    for (count_repeat = 0; count_repeat < repetir ; ++count_repeat)
    {
    
        for (counter = 0 ;counter < elementos; ++ counter)
        {
            bit_switch(elemento + counter);
        }
        print_display(element_pointer,(void *) background,led_on_void,led_off_void, 11);    //acá esta el problema con el back y frontend
        al_rest(0.3);
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
