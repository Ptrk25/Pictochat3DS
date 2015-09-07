#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <ctype.h>
#include "color.h"
#include "draw.h"
#include "messages.h"
#include "keyboard.h"
#include "connection.h"


Key keys[51];
int max_length = 99;
int cache_length = 0;
char cache[100] = "";

bool set_name = false;
bool shift = false;

int key_init(Key* k, int x, int y, char c) {
    k->key = c;
    
    k->coords.x = x;
    k->coords.y = y;
    
    return 0;
}

int keys_y_add(int y) {
    int i;
    for(i = 0; i <= 50; i++) {
        keys[i].coords.y += y;
    }
    
    return 0;
}

int change_key(Key* k, char c) {
    k->key = c;
    
    return 0;
}

int remove_cache(void) {
    draw_square(1, 1, 319, 70, black, bottom);
    
    return 0;
}
int keys_init(void) {
    //keys
    int i;
    for(i = 0; i <= 50; i++) {
        keys[i].width = 24;
        keys[i].height = 21;
        
        keys[i].selected = false;
    }
    
    key_init(&keys[0], 3, 71, '1');
    key_init(&keys[1], 28, 71, '2');
    key_init(&keys[2], 53, 71, '3');
    key_init(&keys[3], 78, 71, '4');
    key_init(&keys[4], 103, 71, '5');
    key_init(&keys[5], 128, 71, '6');
    key_init(&keys[6], 153, 71, '7');
    key_init(&keys[7], 178, 71, '8'); //made mistake at this one
    key_init(&keys[8], 203, 71, '9');
    key_init(&keys[9], 228, 71, '0');
    key_init(&keys[10], 253, 71, '-');
    key_init(&keys[11], 278, 71, '<');
    
    key_init(&keys[12], 3, 93, 'q');
    key_init(&keys[13], 32, 93, 'w');
    key_init(&keys[14], 57, 93, 'e');
    key_init(&keys[15], 82, 93, 'r');
    key_init(&keys[16], 107, 93, 't');
    key_init(&keys[17], 132, 93, 'y');
    key_init(&keys[18], 157, 93, 'u');
    key_init(&keys[19], 182, 93, 'i'); //made mistake at this one
    key_init(&keys[20], 207, 93, 'o');
    key_init(&keys[21], 232, 93, 'p');
    key_init(&keys[22], 257, 93, '>');
    
    key_init(&keys[23], 3, 115, 'a');
    key_init(&keys[24], 36, 115, 's');
    key_init(&keys[25], 61, 115, 'd');
    key_init(&keys[26], 86, 115, 'f');
    key_init(&keys[27], 111, 115, 'g');
    key_init(&keys[28], 136, 115, 'h');
    key_init(&keys[29], 161, 115, 'j');
    key_init(&keys[30], 186, 115, 'k');
    key_init(&keys[31], 211, 115, 'l');
    key_init(&keys[32], 236, 115, '\'');
    key_init(&keys[33], 261, 115, '=');
    key_init(&keys[34], 286, 115, '/');
    
    key_init(&keys[35], 3, 137, 'z');
    key_init(&keys[36], 40, 137, 'x');
    key_init(&keys[37], 65, 137, 'c');
    key_init(&keys[38], 90, 137, 'v');
    key_init(&keys[39], 115, 137, 'b');
    key_init(&keys[40], 140, 137, 'n');
    key_init(&keys[41], 165, 137, 'm');
    key_init(&keys[42], 190, 137, ',');
    key_init(&keys[43], 215, 137, '.');
    key_init(&keys[44], 240, 137, '?');
    key_init(&keys[45], 265, 137, '!');
    key_init(&keys[46], 290, 137, '@');
    
    key_init(&keys[47], 3, 159, ' ');
    key_init(&keys[48], 40, 159, ' ');
    key_init(&keys[49], 77, 159, ' ');
    key_init(&keys[50], 276, 159, ' ');
    
    keys_y_add(58);
    
    keys[12].width = 28; //q key
    keys[23].width = 32; //a key
    keys[35].width = 36; //z key
    
    keys[11].width = 39; //backspace
    keys[22].width = 60; //enter key
    keys[34].width = 31; //slash
    keys[46].width = 27; //@-sign
    
    keys[47].width = 36; //shift
    keys[48].width = 36; //change
    keys[49].width = 198;//space
    keys[50].width = 41; //shift
    
    return 0;
}

int keys_draw(void) {
    int i;
    for(i = 0; i <= 50; i++) {
        draw_square(keys[i].coords.x - 1, keys[i].coords.y - 1, keys[i].width + 2, keys[i].height + 2, border_keyboard, bottom);
        
        if(keys[i].selected) { //if we want antoher background:hover color
            //draw_square(keys[i].coords.x, keys[i].coords.y, keys[i].width, keys[i].height, hover_keys, bottom);
        }
        else {
            draw_square(keys[i].coords.x, keys[i].coords.y, keys[i].width, keys[i].height, background_keyboard, bottom);
        }
        DrawCharacter(bottom, keys[i].key, keys[i].coords.x + keys[i].width / 2 - 2, keys[i].coords.y + keys[i].height / 2 + 2, black);
    }
    
    remove_cache();
    DrawString(bottom, cache, 10, 10, white);
    
    return 0;
}

char *get_keys(void) {
    return cache;
}
int reset_keys(void) {
    cache_length = 0;
    memset(cache, 0, strlen(cache));
    remove_cache();
    return 0;
}
bool check_hover(touchPosition touch) {
    bool changed = false;
    int i;
    for(i = 0; i <= 50; i++) {
        if(touch.px >= keys[i].coords.x && touch.px <= (keys[i].coords.x + keys[i].width) && touch.py >= keys[i].coords.y && touch.py <= (keys[i].coords.y + keys[i].height)) {
            if(keys[i].selected == false) {
                keys[i].selected = true;
                changed = true;
            }
        }
        else {
            if(keys[i].selected == true) {
                keys[i].selected = false;
                changed = true;
                
                if(touch.px == 0 && touch.py == 0) {
                    if(i == 11) { //backspace
                        if(cache_length > 0) {
                            cache[--cache_length] = 0;//cache[strlen(cache)-1] = 0;
                        }
                    }
                    else if(i == 47 || i == 50) { //shift key
                        int j;
                        shift = !shift;
                        for(j = 0; j < 47; j++) {
                            if(shift) {
                                change_key(&keys[j], (char)toupper((int)keys[j].key));
                            }
                            else {
                                change_key(&keys[j], (char)tolower((int)keys[j].key));
                            }
                        }
                    }
                    else if(i == 22) {//enter key
                        send_keys();
                    }
                    else {
                        if(cache_length < max_length) {
                            cache[cache_length++] = keys[i].key;//cache = append(cache, keys[i].key);
                        }
                    }
                }
            }
        }
    }
    return false || changed;
}

int send_keys(void) {
    char message[50];
    memset(message, 0, sizeof(message));

    strcpy(message, get_keys());
    reset_keys();
    if(sizeof(message) > 0) {
        if(!set_name) {
            char stand[50];

            strcpy(stand, "[NAME]");
            strcat(stand, message);
            strcpy(message, stand);

            set_name = true;
        }
        sock_send(message, sizeof(message));
    }
    
    return 0;
}