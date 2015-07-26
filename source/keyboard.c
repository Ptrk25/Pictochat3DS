#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include "keyboard.h"
#include "color.h"
#include "draw.h"

int max_chars = 40;
char cache[41];
int cache_length = 0;

char azerty[3][10] = {{'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'}, {'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M'}, {'W', 'X', 'C', 'V', 'B', 'N', ',', '?', '.', ' '}};
Key keys[3][10];

void init_keyboard() {
    int i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 10; j++) { //320 width
            keys[i][j].key = azerty[i][j];
            keys[i][j].selected = 0;
        }
    }
}

//draws keyboard on bottom screen
void draw_keyboard(u8* screen) {
    int i, j;
    
    draw_square(0, 0, 320, 240, background_bottom, screen);
    
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 10; j++) { //320 width
            if(keys[2 - i][j].selected == 1) {
                draw_square(j * 32 + 1, 240 - ((i + 1) * 32), 30, 30, hover_keys, screen);
            }
            else {
                draw_square(j * 32 + 1, 240 - ((i + 1) * 32), 30, 30, background_keys, screen);
            }
            DrawCharacter(screen, keys[2 - i][j].key, j * 32 + 14, 240 - ((i + 1) * 32) + 14, white);
        }
    }
    
    draw_square(1, 1, 319, 140, background_text, screen);
    DrawString(screen, cache, 15, 15, white);
}

bool check_keyboard_click(touchPosition touch) {
    bool change = false;
    int i, j, x, y;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 10; j++) { //320 width
            x = j * 32 + 1;
            y = 240 - ((i + 1) * 32);
            if(x <= touch.px && x + 30 >= touch.px && y <= touch.py && y + 30 >= touch.py) {
                if(keys[2 - i][j].selected == 0) {
                    change = true;
                }
                keys[2 - i][j].selected = 1;
                //TODO copy keys[2 - i][j].key into cache
            }
            else {
                if(keys[2 - i][j].selected == 1) { //if it was selected, but isn't anymore
                    keys[2 - i][j].selected = 0;
                    
                    if(touch.px == 0 && touch.py == 0 && cache_length < 28) { //for some reason the 30st pressed key makes the application crash
                        cache[cache_length++] = keys[2 - i][j].key;
                        change = true;
                    }
                }
            }
        }
    }
    return change;
}

void send() {
    if(strlen(cache) > 0) {
        
    }
}