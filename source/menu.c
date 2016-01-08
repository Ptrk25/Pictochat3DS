#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include "color.h"
#include "menu.h"
#include "draw.h"
#include "main.h"
#include "connection.h"

Menupage current_page = MENU_DEFAULT;
int menu_width = 320;
int menu_height = 240;

Button buttons[4][4];
Label userlist[10];

int userlist_count = 0;

void nothing() {
    
}

void quit() {
    hb_quit = true;
}

void button_back() {
    if(current_page == MENU_DEFAULT) {
        keyboard_visible = true;
        force_change = true;
    }
    else {
        current_page = MENU_DEFAULT;
    }
}
void goto_rooms() {
    current_page = MENU_ROOMS;
}
void goto_settings() {
    current_page = MENU_SETTINGS;
}
void ask_list() {
    sock_send("!{list", strlen("!{list"));
}
int menu_init() {
    int i, j;
    for(i = 0; i < 10; i++) {
        userlist[i].x = 25;
        userlist[i].y = 10 + 22 * i;
        userlist[i].width = 365;
        userlist[i].height = 20;
        strcpy(userlist[i].text, "");
        userlist[i].bgcolor = background_keyboard;
        userlist[i].color = black;
        userlist[i].border = black;
        userlist[i].screen = TOP;
    }
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            buttons[i][j].x = 10;
            buttons[i][j].y = 10 + (45 * j);
            buttons[i][j].width = 300;
            buttons[i][j].height = 40;
            buttons[i][j].color = black;
            buttons[i][j].bgcolor = background_keyboard;
            buttons[i][j].border = background_keyboard;
            buttons[i][j].bgcolor_hover = black;;
            buttons[i][j].f = &nothing;
            buttons[i][j].screen = BOTTOM;
        }
    }
    
    buttons[MENU_DEFAULT][0].text = "Back";
    buttons[MENU_DEFAULT][0].f = &button_back;
    
    //buttons[MENU_DEFAULT][1].text = "Rooms";
    //buttons[MENU_DEFAULT][1].f = &goto_rooms;
    buttons[MENU_DEFAULT][1].text = "Comming soon";
    buttons[MENU_DEFAULT][1].f = &nothing;
    
    //buttons[MENU_DEFAULT][2].text = "Settings";
    //buttons[MENU_DEFAULT][2].f = &ask_list;
    //buttons[MENU_DEFAULT][2].f = &goto_settings;
    buttons[MENU_DEFAULT][2].text = "Comming soon";
    buttons[MENU_DEFAULT][2].f = &nothing;
    
    buttons[MENU_DEFAULT][3].text = "Exit";
    buttons[MENU_DEFAULT][3].f = &quit;
    
    
    buttons[MENU_ROOMS][0].text = "Join room 1";
    
    buttons[MENU_ROOMS][1].text = "Join room 2";
    
    buttons[MENU_ROOMS][2].text = "Join room 3";
    
    buttons[MENU_ROOMS][3].text = "Back";
    buttons[MENU_ROOMS][3].f = &button_back;
    
    
    return 0;
}


int menu_check_buttons(touchPosition touch) {
    bool changed = false;
    int i;
    for(i = 0; i < 4; i++) {
        if(buttons[current_page][i].text != NULL) {
            if(touch.px >= buttons[current_page][i].x && touch.px <= (buttons[current_page][i].x + buttons[current_page][i].width) && touch.py >= buttons[current_page][i].y && touch.py <= (buttons[current_page][i].y + buttons[current_page][i].height)) {
                if(buttons[current_page][i].selected == false) {
                    buttons[current_page][i].selected = true;
                    changed = true;
                }
            }
            else {
                if(buttons[current_page][i].selected == true) {
                    buttons[current_page][i].selected = false;
                    changed = true;

                    if(touch.px == 0 && touch.py == 0) {
                        //execute it's function
                        buttons[current_page][i].f();
                    }
                }
            }
        }
    }
    
    return changed;
}

int menu_draw(u8* screen) {
    int i;
    
    //draw background
    draw_square(1, 1, menu_width, menu_height, black, screen);
    
    for(i = 0; i < 4; i++) {
        if(buttons[current_page][i].text != NULL) {
            //draw border
            draw_square(buttons[current_page][i].x, buttons[current_page][i].y, buttons[current_page][i].width, 1, buttons[current_page][i].border, screen);
            draw_square(buttons[current_page][i].x, buttons[current_page][i].y, 1, buttons[current_page][i].height, buttons[current_page][i].border, screen);
            draw_square(buttons[current_page][i].x + buttons[current_page][i].width - 1, buttons[current_page][i].y, 1, buttons[current_page][i].height, buttons[current_page][i].border, screen);
            draw_square(buttons[current_page][i].x, buttons[current_page][i].y + buttons[current_page][i].height - 1, buttons[current_page][i].width, 1, buttons[current_page][i].border, screen);
            
            if(!buttons[current_page][i].selected) {
                draw_square(buttons[current_page][i].x + 1, buttons[current_page][i].y + 1, buttons[current_page][i].width - 2, buttons[current_page][i].height - 2, buttons[current_page][i].bgcolor, screen);
                DrawString(screen, buttons[current_page][i].text, buttons[current_page][i].x + buttons[current_page][i].width / 2 - strlen(buttons[current_page][i].text) * FONT_SIZE / 2, buttons[current_page][i].y + buttons[current_page][i].height / 2, buttons[current_page][i].color);
            }
            else {
                draw_square(buttons[current_page][i].x + 1, buttons[current_page][i].y + 1, buttons[current_page][i].width - 2, buttons[current_page][i].height - 2, background_message_selected, screen);
                DrawString(screen, buttons[current_page][i].text, buttons[current_page][i].x + buttons[current_page][i].width / 2 - strlen(buttons[current_page][i].text) * FONT_SIZE / 2, buttons[current_page][i].y + buttons[current_page][i].height / 2, white);
            }
        }
    }
    
    for(i = 0; i < 10; i++) {
        draw_square(userlist[i].x, userlist[i].y,userlist[i].width, 1, userlist[i].border, top);
        draw_square(userlist[i].x, userlist[i].y, 1, userlist[i].height, userlist[i].border, top);
        draw_square(userlist[i].x + userlist[i].width - 1, userlist[i].y, 1, userlist[i].height, userlist[i].border, top);
        draw_square(userlist[i].x, userlist[i].y + userlist[i].height - 1, userlist[i].width, 1, userlist[i].border, top);
    
        draw_square(userlist[i].x + 1, userlist[i].y + 1, userlist[i].width - 2, userlist[i].height - 2, background_message_selected, top);
        DrawString(top, userlist[i].text, userlist[i].x + userlist[i].width / 2 - strlen(userlist[i].text) * FONT_SIZE / 2, userlist[i].y + userlist[i].height / 2, white);
    }
    

    return 0;
}

void userlist_reset() {
    int i;
    for(i = 0; i < 10; i++) {
        memset(userlist[i].text, 0, strlen(userlist[i].text));
    }
    userlist_count = 0;
}
void userlist_add(char *text) {
    if(userlist_count < 10) {
        strcpy(userlist[userlist_count].text, text);
        userlist_count += 1;
    }
}