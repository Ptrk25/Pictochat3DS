/* 
 * File:   menu.h
 * Author: bert
 *
 * Created on 12 september 2015, 19:39
 */

#ifndef MENU_H
#define	MENU_H

typedef enum {
    MENU_DEFAULT,
    MENU_ROOMS,
    MENU_SETTINGS,
}Menupage;

typedef enum Screen {
    TOP,
    BOTTOM
}Screen;

typedef struct Button {
    int x;
    int y;
    int width;
    int height;
    char* text;
    
    Color bgcolor;
    Color color;
    Color border;
    
    Color bgcolor_hover;
    
    Screen screen;
    bool selected;
    void (*f)();
}Button;

typedef struct Label {
    int x;
    int y;
    int width;
    int height;
    char text[30];
    
    Color bgcolor;
    Color color;
    Color border;
    
    Screen screen;
}Label;

int menu_init();
int menu_check_buttons(touchPosition touch);
int menu_draw(u8* screen);

void userlist_add(char *text);
void userlist_reset();

#endif	/* MENU_H */

