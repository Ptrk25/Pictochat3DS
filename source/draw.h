/* 
 * File:   draw.h
 * Author: bert
 *
 * Created on 21 juli 2015, 16:46
 */
#pragma once

#ifndef DRAW_H
#define DRAW_H

#define BYTES_PER_PIXEL	3  //Our color buffer accepts 24-bits color.
#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	240
#define SCREEN_SIZE	(BYTES_PER_PIXEL*SCREEN_WIDTH*SCREEN_HEIGHT)
#define FONT_SIZE	8
#define WIDTH           400
#define HEIGHT          240
#define TOPSIZE         288000
#define BOTTOMSIZE      230400

u8* top;
u8* bottom;

void DrawCharacter(u8 *screen, char character, u32 x, u32 y, Color color);
void DrawString(u8 *screen, const char *str, u32 x, u32 y, Color color);
void color_pixel(int x, int y, Color color, u8* screen);
void draw_square(int x, int y, int width, int height, Color color, u8* screen);

#endif