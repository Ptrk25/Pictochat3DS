/* 
 * File:   color.h
 * Author: bert
 *
 * Created on 21 juli 2015, 23:14
 */
#pragma once

#ifndef COLOR_H
#define	COLOR_H

typedef struct color {
    u8 r, g, b;
}Color;

Color background_top;
Color background_bottom;
Color background_stripes_outside;
Color background_stripes_inside;

Color background_message;
Color background_message_selected;
Color border_message;
Color message_stripes;

Color background_leftborder;

Color background_keys;
Color hover_keys;
Color color_keys;

Color background_text;
Color color_text;

Color unnamed_1;
Color unnamed_2;
Color unnamed_3;
Color unnamed_4;
Color unnamed_5;
Color unnamed_6;

Color white;
Color black;

void init_colors();

#endif

