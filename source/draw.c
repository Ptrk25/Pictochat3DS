#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include "color.h"
#include "draw.h"
#include "font.h"

#include <math.h>
#define PI 3.14159265

void DrawCharacter(u8 *screen, char character, u32 x, u32 y, Color color)
{
    u32 yy;
    u8 *screenPos, *screenStart = screen + (x * SCREEN_HEIGHT + SCREEN_HEIGHT - y - 1) * BYTES_PER_PIXEL;

    u32 charPos = character * FONT_SIZE;
    u8 charVal;
    for (screenPos = screenStart; screenPos < screenStart + (SCREEN_HEIGHT - FONT_SIZE) * BYTES_PER_PIXEL * FONT_SIZE; screenPos += (SCREEN_HEIGHT - FONT_SIZE) * BYTES_PER_PIXEL)
    {
        charVal = font[charPos++];
        for (yy = FONT_SIZE; yy--;)
        {
            if (charVal & 1)
            {
                *(screenPos++) = color.r;
                *(screenPos++) = color.g;
                *(screenPos++) = color.b;
            }
            else
            {
                screenPos += 3;
            }
            charVal >>= 1;
        }
    }
}

void DrawString(u8 *screen, const char *str, u32 x, u32 y, Color color)
{
    u32 i;
    for (i = 0; i < strlen(str); i++){
        DrawCharacter(screen, str[i], x + i * FONT_SIZE, y, color);
    }
}

void color_pixel(int x, int y, Color color, u8* screen) {
    y = HEIGHT - y;
    int hulp = x;
    x = y;
    y = hulp;
    
    u32 v=(x + y * HEIGHT) * 3;
    
    if((screen == top && v < 288000 && v > 0) || (v < 230400 && v > 0)) {
        screen[v] = color.r;
        screen[v + 1] = color.g;
        screen[v + 2] = color.b;
    }
}

void draw_square(int x, int y, int width, int height, Color color, u8* screen) {
    int i, j;
    for(i = 0; i < width && i >= 0; i++) {
        for(j = 0; j < height && i >= 0; j++) {
            color_pixel(x + i, y + j, color, screen);
        }
    }
}

void color_pixel_rgb(int x, int y, u8 r, u8 g, u8 b, u8* screen) {
    Color hulp;
    hulp.r = r;
    hulp.g = g;
    hulp.b = b;
    
    color_pixel(x, y, hulp, screen);
}

void draw_square_radius(int x, int y, int width, int height, int radius, Color color, u8* screen) {
    //need to work on this
}

void draw_image(u8 *screen, Image *image, int x, int y, int rotation) {
    int i, j, v, rx, ry;
    for(i = 0; i < image->width; i++) {
        for(j = 0; j < image->height; j++) {
            v = (image->width * j + i) * 3;
            if((u8)image->image[v] != 0xff && (u8)image->image[v + 1] != 0xff && (u8)image->image[v + 2] != 0xff) {
                if(rotation != 0) {
                    rx = (int)round((i - image->width / 2) * cos(rotation * PI/180) - (j - image->height / 2) * sin(rotation * PI/180));
                    ry = (int)round((i - image->width / 2) * sin(rotation * PI/180) + (j - image->height / 2) * cos(rotation * PI/180));
                    color_pixel_rgb(x + rx + image->width / 2, y + ry + image->height / 2, (u8)image->image[v], (u8)image->image[v + 1], (u8)image->image[v + 2], screen);
                }
                else {
                    color_pixel_rgb(x + i, y + j, (u8)image->image[v], (u8)image->image[v + 1], (u8)image->image[v + 2], screen);
                }
            }
        }
    }
}

void draw_image_center(u8 *screen, Image *image, int x, int y, int width, int height, int rotation) {
    draw_image(screen, image, x + width / 2 - image->width / 2, y + height / 2 - image->height / 2, rotation);
}