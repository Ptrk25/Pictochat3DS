/* 
 * File:   keyboard.h
 * Author: bert
 *
 * Created on 21 juli 2015, 17:03
 */

#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

void init_keyboard();
void draw_keyboard(u8* screen);
void check_keyboard_click(touchPosition touch);
void send();

#endif

