#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include "color.h"
#include "draw.h"

char a[2][14];

int userlist_draw(void) {
    //draw square
    draw_square(10, 10, 300, 15, background_keyboard, bottom);
    DrawString(bottom, "ONLINE USERS", 12, 19, black);
    draw_square(10, 20, 300, 220, white, bottom);
    
    int i;
    for(i = 0; i < 2 && i < 10; i++) {
        draw_square(13, 28 + i * 25, 294, 20, background_keyboard, bottom);
        DrawString(bottom, a[i], 15, 28 + i * 25 + 10, black);
    }
    for(i = 10; i < 20 && i < 10; i++) {
        draw_square(13, 28 + i * 25, 294, 20, background_keyboard, bottom);
        DrawString(bottom, a[i], 15, 28 + i * 25 + 10, black);
    }
    
    return 0;
}
int userlist_read(void) {
    strcpy(a[0], "blah");
    strcpy(a[1], "hmm");
    
    return 0;
}