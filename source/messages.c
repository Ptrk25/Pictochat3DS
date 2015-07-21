#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include "color.h"
#include "draw.h"
#include "messages.h"

struct message {
    char* message;
    int sender;
    Color color;
};

int max_messages = 100;
int messages_count = 0;
int messages_start = 0;
struct message messages[100];
int selected_message = 0;

void init_messages() {
    int i;
    for(i = 0; i < max_messages; i++) {
        messages[i].message = "";
        messages[i].sender = 0;
    }
}
void add_message(char* message, int sender, Color color) {
    messages[messages_count].message = message;
    messages[messages_count].sender = sender;
    messages[messages_count].color = color;
    messages_count++;
    selected_message++;
}

void selection_up() {
    if(selected_message > 1)
        selected_message--;
}
void selection_down() {
    if(selected_message < messages_count)
        selected_message++;
}

void draw_messages(u8* top) {
    //lets start drawing the current messages
    int i;
    
    int current = messages_count;
    if(current > 38) { //temp fix for to many messages
        current = 38;
    }
    for(i = current; i > 0; i--) { //draw those stripes on the left
        draw_square(4, HEIGHT - 25 - i * 5, 12, 2, message_stripes, top);
    }
    
    current = messages_count;
    if(current > 9) { //temp fix for to many messages
        current = 9;
    }
    for(i = current; i > 0; i--) { //there only fit 7 messages maximum on the screen
        struct color hulp;
        if(messages_count - i + 1 == selected_message) {
            hulp = background_message_selected;
        }
        else {
            hulp = background_message;
        }
        
        draw_square(25, HEIGHT - 25 - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        draw_square(25, HEIGHT - 24  - (i - 1) * 25, WIDTH - 30, 1, white, top);
        draw_square(25, HEIGHT - 23  - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        
        draw_square(24, HEIGHT - 24 - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(25, HEIGHT - 24  - (i - 1) * 25, 1, 1, white, top);
        
        draw_square(23, HEIGHT - 23 - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(24, HEIGHT - 23 - (i - 1) * 25, 1, 1, white, top);
        
        draw_square(22, HEIGHT - 22 - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(23, HEIGHT - 22 - (i - 1) * 25, 1, 1, white, top);
        draw_square(24, HEIGHT - 22 - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        
        draw_square(21, HEIGHT - 21 - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(22, HEIGHT - 21 - (i - 1) * 25, 1, 1, white, top);
        draw_square(23, HEIGHT - 21 - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        
        int j;
        for(j = 0; j < 12; j++) {
            draw_square(21, HEIGHT - (20 - j) - (i - 1) * 25, 1, 1, hulp, top);
            draw_square(22, HEIGHT - (20 - j)  - (i - 1) * 25, 1, 1, white, top);
            
            draw_square(23, HEIGHT - (20 - j)  - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        }
        
        draw_square(21, HEIGHT - (19 - j + 1) - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(22, HEIGHT - (19 - j + 1) - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(23, HEIGHT - (19 - j + 1) - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        
        draw_square(22, HEIGHT - (18 - j + 1) - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(23, HEIGHT - (18 - j + 1) - (i - 1) * 25, 1, 1, white, top);
        draw_square(24, HEIGHT - (18 - j + 1)  - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        
        draw_square(23, HEIGHT - (17 - j + 1) - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(24, HEIGHT - (17 - j + 1) - (i - 1) * 25, 1, 1, white, top);
        
        draw_square(24, HEIGHT - (16 - j + 1)  - (i - 1) * 25, 1, 1, hulp, top);
        draw_square(25, HEIGHT - (16 - j + 1)  - (i - 1) * 25, 1, 1, white, top);
        
        draw_square(25, HEIGHT - (17 - j + 1)  - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        draw_square(25, HEIGHT - (16 - j + 1)  - (i - 1) * 25, WIDTH - 30, 1, white, top);
        draw_square(25, HEIGHT - (15 - j + 1)  - (i - 1) * 25, WIDTH - 30, 1, hulp, top);
        
        //DRAW HERE SOME TEXT ARROUND COORDS (20, 20)
        //IF IT WORKS, TRY THIS TEXT: 
        DrawString(top, messages[messages_count - i].message, 30, HEIGHT - (20 - j)  - (i - 1) * 25 - FONT_SIZE / 2, messages[messages_count - i].color);
    }
}