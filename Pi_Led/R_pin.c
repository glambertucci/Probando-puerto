#include "R_pin.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


static void set_output_pin (char * pin, char led_state);
static void unset_output_pin (char * pin, char led_state);

static void export(char * pin);
static void output_set(char * pin);
static void unexport(char * pin);

void set_leds (void * pointer)
{	
    b1_t * pin = pointer;

    set_output_pin (LED_1, (pin->b0) + '0');
    set_output_pin (LED_2, (pin->b1) + '0');		
    set_output_pin (LED_3, (pin->b2) + '0');
    set_output_pin (LED_4, (pin->b3) + '0');
    set_output_pin (LED_5, (pin->b4) + '0');
    set_output_pin (LED_6, (pin->b5) + '0');
    set_output_pin (LED_7, (pin->b6) + '0');
}

/////////////////////////////////////////////////////////

void unset_leds (void)
{
    unset_output_pin (LED_1, '0');
    unset_output_pin (LED_2, '0');		
    unset_output_pin (LED_3, '0');
    unset_output_pin (LED_4, '0');
    unset_output_pin (LED_5, '0');
    unset_output_pin (LED_6, '0');
    unset_output_pin (LED_7, '0');
}

/////////////////////////////////////////////////////////

static void set_output_pin ( char * pin, char led_state )
{
    export( (char *)pin);
    output_set((char *)pin);
    state_set((char *)pin,led_state);
}

////////////////////////////////////////////////////////
static void unset_output_pin (char * pin, char led_state)
{
	state_set(pin,led_state);   
	unexport(pin);
}

/////////////////////////////////////////////////////////

static void unexport(char * pin)
{
	FILE *handle_unexport;
	int nWritten;
	if ((handle_unexport =  fopen("/sys/class/gpio/unexport","w")) == NULL)
	{	
   	printf("Cannot open UNEXPORT File. Try again later.\n");
   	exit(1);
	}
	nWritten=fputs(pin,handle_unexport); 
	if (nWritten==-1)
	{
   		printf ("Cannot UNEXPORT PIN . Try again later.\n");
   		exit(1);
	}	
	else
//    		printf("UNEXPORT File opened succesfully \n");
		
   fclose(handle_unexport);  // Be carefull do this for EACH pin !!!

}

/////////////////////////////////////////////////////////

static void export(char * pin)
{
	FILE *handle_export;
	int nWritten;
	if ((handle_export =  fopen("/sys/class/gpio/export","w")) == NULL)
	{	
   	printf("Cannot open EXPORT File. Try again later.\n");
   	exit(1);
	}
	nWritten=fputs(pin,handle_export); 
	if (nWritten==-1)
	{
   		printf ("Cannot EXPORT PIN . Try again later.\n");
   		exit(1);
	}	
//	else
//    		printf("EXPORT File opened succesfully \n");
		
   fclose(handle_export);  // Be carefull do this for EACH pin !!!

}

/////////////////////////////////////////////////////////

static void output_set(char * pin)
{
    FILE * handle_direction;
    int nWritten;

    char * part1 = "/sys/class/gpio/gpio";
    char * part3 = "/direction";
    char full_address [100];
	
    strcpy(full_address, part1 );
    strcat(full_address, pin);
    strcat(full_address, part3);
	
    if ((handle_direction = fopen(full_address,"w")) == NULL)
    {
	printf("Cannot open DIRECTION File");
	exit(1);
    }
// Set pin Direction
				
    if ((nWritten=fputs("out",handle_direction))==-1)
    {	
	printf("Cannot open DIRECTION pin. Try again later.\n");
	exit(1);
    }
//  else
//	printf("DIRECTION File for PIN opened succesfully\n");
    		
    fclose(handle_direction); // Be carefull do this for EACH pin !!!
}

/////////////////////////////////////////////////////////

void state_set(char * pin, char led_state)
{
    FILE * handle;

    char * part1 = "/sys/class/gpio/gpio";
    char * part3 = "/value";
    char full_address [100];
	
    strcpy(full_address, part1);
    strcat(full_address, pin);
    strcat(full_address, part3);

    if ((handle = fopen(full_address,"w")) == NULL)
    {
    	printf("Cannot open device. Try again later.\n");
    	exit(1);
    }
//  else
//        printf("Device successfully opened\n");

    if(fputc(led_state ,handle)==-1) // Set pin low
    {
	printf("Clr_Pin: Cannot write to file. Try again later.\n");
	exit(1);
    }
//    else
//	printf("Write to file %s successfully done.\n",full_address);

    fclose(handle);
}


