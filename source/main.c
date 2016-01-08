#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include "color.h"
#include "draw.h"
#include "messages.h"
#include "connection.h"
#include "keyboard.h"
#include "userlist.h"
#include "audio.h"
#include "menu.h"
#include "main.h"
#include "net_debugger.h"

int cache;
bool hb_quit = false;
bool keyboard_visible = true;
bool force_change = false;

void init() {
    cache = 0;

    init_colors();
    keys_init();
    init_messages();
    menu_init();
    userlist_read();
    
    con_init();
    if(con_activate() != 0) {
        add_message("Something went wrong, try again later", 1, white, background_message);
    }
}

void get_buffers() {
    top = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
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
    draw_messages3(top);
}

bool clicked(int x, int y, int width, int height, int touch_x, int touch_y) {
    if(x > touch_x || x + width < touch_x)
        return false;
    
    if(y > touch_y || y + width < touch_y)
        return false;
    
    return true;
}
int main() {
    srvInit();
    aptInit();
    hidInit(NULL);
    httpcInit();
    csndInit();
    gfxInitDefault();
    //ndInit();
    
    init();
    
    audio_load("sdmc:/3ds/pictochat3ds/data/sound/background1.raw");
    
    get_buffers();
    while (true && !hb_quit)
    {
        gspWaitForVBlank();
        hidScanInput();
        
        u32 kDown;
        kDown = hidKeysDown();
        
        u32 kHeld;
        kHeld = hidKeysHeld();
        
        touchPosition touch;
        hidTouchRead(&touch);
        
        get_message();
        
        bool keyboard_click = (keyboard_visible && check_hover(touch)) || (!keyboard_visible && menu_check_buttons(touch));
        bool messages_changed = messages_get_change();
        
        if(keyboard_click || messages_changed || force_change) {
            messages_reset_change();
            force_change = false;
            
            draw_menu();
            if(keyboard_visible) {
                keys_draw();
            }
            else {
                menu_draw(bottom);
            }
            gfxFlushBuffers();
            
            gfxFlushBuffers();
            gfxSwapBuffers();
            get_buffers();
        }
        
        if(kDown & KEY_A) {
            send_keys();
        }
        if(kHeld & KEY_L) {  
            //selection_up();
            
        }
        if(kHeld & KEY_R) {  
            //selection_down();
        }
        if(kDown & KEY_START) {
            keyboard_visible = !keyboard_visible;
            force_change = true;
        }
        if(kDown & KEY_SELECT) {
            
        }
        gfxFlushBuffers();
    }
    
    con_dinit();
    
    //ndExit();
    gfxExit();
    csndExit();
    httpcExit();
    hidExit();
    aptExit();
    srvExit();
    return 0;
}