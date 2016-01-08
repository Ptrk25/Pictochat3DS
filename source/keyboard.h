/* 
 * File:   keyboard.h
 * Author: Bert Bijnens
 *
 * Created on 21 juli 2015, 17:03
 */

#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef struct {
    int x;
    int y;
}Coords;

typedef struct {
    char key;
    
    int width;
    int height;
    
    Coords coords;
    
    bool selected;
}Key;

/**
 * Initializes the necesairy variables to make this work
 */
//void init_keyboard();

/**
 * Draws the keyboard to the given screen
 * 
 * @param screen Screen where the keyboard should be drawed to
 */
//void draw_keyboard(u8* screen);

/**
 * Checks if there has been any keyboard activity in the last tick.
 * If a key has been pressed, it will activate the hover effect.
 * If a key has been released it will be added to the cache
 * 
 * @param touch Variable of type touchPosition with the x and y coordinate of the touch specified
 * @return wheter or not there was any activity
 */
//bool check_keyboard_click(touchPosition touch);

//rij 1: 12
//rij 2: 11
//rij 3: 12
//rij 4: 12
//rij 5: 3
// = 50




int keys_init(void);
int keys_draw(void);
bool check_hover(touchPosition touch);
char *get_keys(void);
int reset_keys(void);
int send_keys(void);

#endif

