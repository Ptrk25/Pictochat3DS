/* 
 * File:   keyboard.h
 * Author: bert
 *
 * Created on 21 juli 2015, 17:03
 */

#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef struct key {
    char key;
    int selected;
}Key;

void init_keyboard();
void draw_keyboard(u8* screen);
bool check_keyboard_click(touchPosition touch);
void send();

#endif

