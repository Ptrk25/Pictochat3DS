#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include "color.h"
#include "draw.h"
#include "font.h"


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
  
    screen[v] = color.r;
    screen[v + 1] = color.g;
    screen[v + 2] = color.b;
}

void draw_square(int x, int y, int width, int height, Color color, u8* screen) {
    int i, j;
    for(i = 0; i < width && i >= 0; i++) {
        for(j = 0; j < height && i >= 0; j++) {
            color_pixel(x + i, y + j, color, screen);
        }
    }
}