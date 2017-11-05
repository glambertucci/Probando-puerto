#include "input_output.h"

//Define para el display instructivo

#define TITLE (0)
#define INDIVIDUAL_LEDS (1)
#define BLINK (2)
#define ON (3)
#define OFF (4)
#define MOUSE (5)
#define BACKGROUND (6)
#define LEAVE (7)
#define INSTRUCTIONS (8)

#define MAX_MESSAGES (9)

//FUNCIONES 

void print_display (void * pointer, void * background,void * led_on_void, void * led_off_void, int elementos)
{
    int counter;
    element * elemento = pointer;
    ALLEGRO_BITMAP * led_on = led_on_void;
    ALLEGRO_BITMAP * led_off = led_off_void;
    
    al_draw_bitmap((ALLEGRO_BITMAP *)background,0,0,0);

    for (counter = 0 ; counter < elementos ; ++counter)
    {      
        if ((elemento + counter)->led_enabled)
        {
            if ( ( (elemento + counter)->led_on) )
            {
                al_draw_bitmap(led_on,(elemento + counter)->position_x,(elemento + counter)->position_y,0);
  
            }
            else if (! ( (elemento + counter)->led_on ) )
            {
                al_draw_bitmap(led_off,(elemento + counter)->position_x,(elemento + counter)->position_y,0);
            }
        }
        else if (! ( (elemento + counter)->led_enabled))
        {
           al_draw_bitmap((elemento + counter)->bitmap,(elemento + counter)->position_x,(elemento + counter)->position_y,0);
        }

    }

    al_flip_display();
}

bool click_button(int mouse_x, int mouse_y, int button_x, int button_y , int lenght_x, int lenght_y )
{
    bool valid = false; 
    if ( (mouse_x > button_x) && (mouse_x < ( button_x + lenght_x) ))
    {
        if ((mouse_y > button_y) && (mouse_y < ( button_y + lenght_y) ))
        {
            valid = true;
        }
    }
    return valid;
}

int button_pressed (int mouse_x, int mouse_y, void * pointer2, int elements)
{
    element * pointer = pointer2;
    int counter;
    bool valid = false;
    
    for (counter = 0 ; !valid && (counter < (elements+1)) ; ++counter) // Se fija si se toco a algun boton
    {
        valid = click_button(mouse_x,mouse_y,(pointer + counter)->position_x,(pointer + counter)->position_y, (pointer + counter)->lenght_x, (pointer + counter)->lenght_y);
    }
    
    if (counter == elements + 1)   // Si no esta en la lista, es por que no toca a ningun boton
    {
        counter = -1;
    }
    else
    {
        --counter;
    }
    
    return counter;
}

int display_instructions (const char * archivo_letra_titulo, const char * archivo_letra_cuerpo, const char * color_letra)
{
    ALLEGRO_DISPLAY * instruction_display = NULL;
    ALLEGRO_EVENT_QUEUE * event_line_ins = NULL;
    ALLEGRO_FONT * title = NULL;
    ALLEGRO_FONT * body = NULL;
    
    int counter;
    bool exit = false;
    
    const char * messages [MAX_MESSAGES];   // Hago un arreglo de punteros constantes a string, que son
                                            // las instrucciones
    const char * color = "white";
    messages[TITLE] = "- Instrucciones";
    messages[INDIVIDUAL_LEDS] = "- Las teclas del 0 al 7 prenden y apagan los leds individualmente";
    messages[BLINK] = "- La tecla 'b' hace que los leds parpadeen en su estado actual";
    messages[ON] = "- La tecla 's' prende todos los leds";
    messages[OFF] = "- la tecla 'c' apaga todos los leds";
    messages[MOUSE] = "- Todas las acciones tambien se pueden realizar con el mouse";
    messages[BACKGROUND] = "- Podes cambiar el fondo de pantalla usando las teclas 'F1' y 'F2' ";
    messages[INSTRUCTIONS] = "- Para cerrar este menu, toca la tecla 'tab', para abrirlo toca 'enter'";
    messages[LEAVE] = "- Para salir del programa toca la telca 'escape' ";

    
    al_init_font_addon();
    al_init_ttf_addon();
    
    if ( !(instruction_display = al_create_display(SCREEN_W, SCREEN_H)) ) // Crea el display
    {
        return -1;
    }
    
    if (!(event_line_ins = al_create_event_queue())) // Crea la event Queue
    {
        al_destroy_display(instruction_display);
        return -1;
    }
    
    if (!(title = al_load_ttf_font(archivo_letra_titulo, 32,0))) // Carga la fuente del titulo
    {
        al_destroy_display(instruction_display);
        al_destroy_event_queue(event_line_ins);
        return -1;
    }
    
    if (!(body = al_load_ttf_font(archivo_letra_cuerpo, 20,0))) // Carga la fuente del cuerpo
    {
        al_destroy_display(instruction_display);
        al_destroy_event_queue(event_line_ins);
        return -1;
    }
    
    al_register_event_source(event_line_ins,al_get_display_event_source(instruction_display));
    al_register_event_source(event_line_ins,al_get_keyboard_event_source()); // Permito que reciva eventos del teclado y del display
                //Escribo el titulo
    al_draw_text(title,al_color_name(color_letra),SCREEN_W / 2, 25, ALLEGRO_ALIGN_CENTER,messages[TITLE]);
                // Escribo los mensajes
    for (counter = INDIVIDUAL_LEDS; counter < MAX_MESSAGES ; ++counter)
    {
        al_draw_text(body,al_color_name(color_letra),10,50 + counter * 30 , ALLEGRO_ALIGN_LEFT,messages[counter]);
    }
    
    al_flip_display();
    
    while (!exit)
    {
        ALLEGRO_EVENT event;
        
        if (al_get_next_event(event_line_ins,&event))
        {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)  // Mientras no se cierre a la ventaja,
            {                                               // o se toque la tecla tab, no se va a cerrar
                exit = true;                                // el display
            }
            else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_TAB)
                {
                    exit = true;
                }
            }
        }
    }

    al_destroy_display(instruction_display);            // Destruyo todo lo que use
    al_destroy_event_queue(event_line_ins);
    
    return 0;
}


int print_instructions (const char * archivo_letra_titulo, const char * archivo_letra_cuerpo, const char * color_letra)
{

    ALLEGRO_EVENT_QUEUE * event_line_ins = NULL;
    ALLEGRO_FONT * title = NULL;
    ALLEGRO_FONT * body = NULL;
    
    int counter;
    bool exit = false;
    
    const char * messages [MAX_MESSAGES];   // Hago un arreglo de punteros constantes a string, que son
                                            // las instrucciones
    const char * color = "white";
    messages[TITLE] = "Instrucciones";
    messages[INDIVIDUAL_LEDS] = "- Las teclas del 0 al 7 prenden y apagan los leds ";
    messages[BLINK] = "- La tecla 'b' hace que los leds parpadeen en su estado actual";
    messages[ON] = "- La tecla 's' prende todos los leds";
    messages[OFF] = "- la tecla 'c' apaga todos los leds";
    messages[MOUSE] = "- Todas las acciones tambien se pueden realizar con el mouse";
    messages[BACKGROUND] = "- Podes cambiar el fondo de pantalla usando las teclas 'F1' y 'F2' ";
    messages[INSTRUCTIONS] = "- Para cerrar este menu, toca la tecla 'tab', para abrirlo toca 'enter'";
    messages[LEAVE] = "- Para salir del programa toca la telca 'escape' ";

    al_clear_to_color(al_color_name("black"));  
    
    al_init_font_addon();
    al_init_ttf_addon();
    
    if (!(event_line_ins = al_create_event_queue())) // Crea la event Queue
    {
        return -1;
    }
    
    if (!(title = al_load_ttf_font(archivo_letra_titulo, 32,0))) // Carga la fuente del titulo
    {
        al_destroy_event_queue(event_line_ins);
        return -1;
    }
    
    if (!(body = al_load_ttf_font(archivo_letra_cuerpo, 20,0))) // // Carga la fuente del cuerpo
    {
        al_destroy_event_queue(event_line_ins);
        return -1;
    }
    
    al_register_event_source(event_line_ins,al_get_keyboard_event_source()); // Permito que reciva eventos del teclado y del display
                //Escribo el titulo
    al_draw_text(title,al_color_name(color_letra),SCREEN_W / 2, 25, ALLEGRO_ALIGN_CENTER,messages[TITLE]);
                // Escribo los mensajes
    for (counter = INDIVIDUAL_LEDS; counter < MAX_MESSAGES ; ++counter)
    {
        al_draw_text(body,al_color_name(color_letra),10,50 + counter * 30 , ALLEGRO_ALIGN_LEFT,messages[counter]);
    }
    
    al_flip_display();
    
    while (!exit)
    {
        ALLEGRO_EVENT event;
        
        if (al_get_next_event(event_line_ins,&event))
        {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_TAB)
                {
                    exit = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    exit = true;
                }
            }
        }
    }

    al_destroy_event_queue(event_line_ins);
    al_destroy_font(body);
    al_destroy_font(title);
    
    return 0;
}
