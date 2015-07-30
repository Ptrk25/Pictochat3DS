/* 
 * File:   draw.h
 * Author: bert bijnens
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

/**
 * Draws a char to the specified coordinates
 * 
 * @param screen Screen where the character should be drawed to
 * @param character Character that will be drawed
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param color Textcolor in the Color format
 */
void DrawCharacter(u8 *screen, char character, u32 x, u32 y, Color color);

/**
 * Draws a string to the specified coordinates
 * 
 * @param screen Screen where the character should be drawed to
 * @param str String that will be drawed
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param color Textcolor in the Color format
 */
void DrawString(u8 *screen, const char *str, u32 x, u32 y, Color color);

/**
 * Draws a pixel in the given color
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param color Textcolor in the Color format
 * @param screen Screen where the character should be drawed to
 */
void color_pixel(int x, int y, Color color, u8* screen);

/**
 * Draws a rectangle in the given color
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param width The widht of the rectangle
 * @param height The height of hte rectangle
 * @param color Textcolor in the Color format
 * @param screen Screen where the character should be drawed to
 */
void draw_square(int x, int y, int width, int height, Color color, u8* screen);

void draw_square_radius(int x, int y, int width, int height, int radius, Color color, u8* screen);
#endif