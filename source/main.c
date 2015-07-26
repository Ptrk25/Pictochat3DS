#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include "color.h"
#include "draw.h"
#include "keyboard.h"
#include "messages.h"

int cache;

void init() {
    cache = 0;

    init_colors();
    init_keyboard();
    init_messages();
    
    add_message("You joined the room", 1, white, black);
    add_message("This one is newer", 1, white, background_message);
    add_message("Wow, we're chatting", 1, white, background_message);
    add_message("The latest message", 1, white, background_message);
}

void get_buffers() {
    //memset(top, 0, TOPSIZE); //endabled in V38
    top = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    //memset(bottom, 0, BOTTOMSIZE); //endabled in V38
    bottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
}
void draw_lines() { //9C
    int i, j;
    for(i = 0; i < WIDTH; i++) {
        for(j = 1; j < HEIGHT; j += 8) {
            color_pixel(i, j, background_stripes_outside, top);
            color_pixel(i, j + 1, background_stripes_inside, top);
            color_pixel(i, j + 2, background_stripes_inside, top);
            color_pixel(i, j + 3, background_stripes_outside, top);
        }
    }
}
void draw_sidebar() {
    draw_square(0, 0, 19, HEIGHT, background_leftborder, top);
}
void draw_connection_status() {
    draw_square(1, 2, 16, 16, black, top);
    
    //details
    draw_square(2, 3, 14, 1, unnamed_1, top);
    
    draw_square(3, 6, 3, 3, unnamed_2, top);
    draw_square(4, 7, 1, 1, black, top);
    draw_square(4, 9, 1, 5, unnamed_2, top);
    
    //stripes
    draw_square(7, 12, 2, 2, white, top);
    draw_square(10, 9, 2, 5, white, top);
    draw_square(13, 6, 2, 8, white, top);
    
    draw_square(2, 16, 14, 1, unnamed_1, top);
    
    int i;
    for(i = 0; i < 9; i++) {
        draw_square(1 + i * 2, 20, 1, 1, unnamed_3, top);
    }
    
    //draw A
    draw_square(1, HEIGHT - 18, 16, 16, unnamed_4, top);
    draw_square(2, HEIGHT - 17, 14, 14, unnamed_5, top);
}


void draw_menu() {
    draw_square(0, 0, WIDTH, HEIGHT, background_top, top);
    draw_lines();
    draw_sidebar();
    draw_connection_status();
    draw_messages(top);
}

bool clicked(int x, int y, int width, int height, int touch_x, int touch_y) {
    if(x > touch_x || x + width < touch_x)
        return false;
    
    if(y > touch_y || y + width < touch_y)
        return false;
    
    return true;
}
int main() {
    bool change = true;
    
    srvInit();
    aptInit();
    hidInit(NULL);
    gfxInitDefault();
 
    init();
    
    get_buffers();
    //gfxSwapBuffers();
    while (aptMainLoop())
    {
        
        gspWaitForVBlank();
        hidScanInput();
        
        u32 kDown;
        kDown = hidKeysDown();
        
        touchPosition touch;
        hidTouchRead(&touch);
        
        if(change == true || check_keyboard_click(touch)) {
            draw_keyboard(bottom);
            gfxFlushBuffers();
            change = true;
        }

        if(change) {
            draw_menu();
            gfxFlushBuffers();
            gfxSwapBuffers();
            get_buffers();
            change = false;
        }
        
        
        if(kDown & KEY_A) {  
            add_message("You clicked A", 1, white, background_message);
            change = true;
        }
        if(kDown & KEY_B) {  
            add_message("You clicked B", 1, white, background_message);
            change = true;
        }
        if(kDown & KEY_L) {  
            selection_up();
            change = true;
        }
        if(kDown & KEY_R) {  
            selection_down();
            change = true;
        }
        if(kDown & KEY_START) {
            break;
        }
        
        gfxFlushBuffers();
    }

    gfxExit();
    hidExit();
    aptExit();
    srvExit();
    return 0;
}
