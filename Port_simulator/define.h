/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   define.h
 * Author: lucas
 *
 * Created on May 27, 2017, 11:26 AM
 */

// Esta es la estructura sobre la cual se trabaja
#ifndef DEFINE_H
#define DEFINE_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>

typedef struct
{
    float position_x;
    float position_y;
    int lenght_x;
    int lenght_y;
    bool led_on;
    bool led_enabled;
    ALLEGRO_BITMAP * bitmap;
    
} element;

#define SCREEN_W (1000)     //Largo y ancho de pantalla 
#define SCREEN_H (527)      

#endif /* DEFINE_H */

