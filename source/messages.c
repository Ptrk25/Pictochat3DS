#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include "color.h"
#include "draw.h"
#include "messages.h"

int max_messages = 500;
int messages_count = 0;
int messages_start = 0;
Message messages[500];
int selected_message = 0;

bool change = false;

void init_messages() {
    int i;
    for(i = 0; i < max_messages; i++) {
        strcpy(messages[i].message,"");
        messages[i].sender = 0;
    }
    change = true;
}
void add_message(char* message, int sender, Color color, Color bgcolor) {
    if(messages_count < max_messages - 1) {
        strcpy(messages[messages_count].message, message);
        messages[messages_count].sender = sender;
        messages[messages_count].color = color;
        messages[messages_count].bgcolor = bgcolor;
        messages_count++;
        selected_message++;
        change = true;
    }
    else {
        if(messages_count < max_messages) {
            strcpy(messages[messages_count].message, "max messages reached, please restart.");
            messages[messages_count].sender = sender;
            messages[messages_count].color = color;
            messages[messages_count].bgcolor = bgcolor;
            messages_count++;
            selected_message++;
            change = true;
        }
    }
}

void selection_up() {
    if(selected_message > 1) {
        selected_message--;
        change = true;
    }
}
void selection_down() {
    if(selected_message < messages_count) {
        selected_message++;
        change = true;
    }
}

void draw_box(u8* top, int index) {
    struct color hulp;
    if(messages_count - index + 1 == selected_message) {
        hulp = background_message_selected;
    }
    else {
        hulp = background_message;
    }

    draw_square(25, HEIGHT - 25 - (index - 1) * 25, WIDTH - 25, 1, hulp, top);
    draw_square(25, HEIGHT - 24  - (index - 1) * 25, WIDTH - 25, 1, white, top);
    draw_square(25, HEIGHT - 23  - (index - 1) * 25, WIDTH - 25, 1, hulp, top);

    draw_square(24, HEIGHT - 24 - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(25, HEIGHT - 24  - (index - 1) * 25, 1, 1, white, top);

    draw_square(23, HEIGHT - 23 - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(24, HEIGHT - 23 - (index - 1) * 25, 1, 1, white, top);

    draw_square(22, HEIGHT - 22 - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(23, HEIGHT - 22 - (index - 1) * 25, 1, 1, white, top);
    draw_square(24, HEIGHT - 22 - (index - 1) * 25, WIDTH - 24, 1, hulp, top);

    draw_square(21, HEIGHT - 21 - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(22, HEIGHT - 21 - (index - 1) * 25, 1, 1, white, top);
    draw_square(23, HEIGHT - 21 - (index - 1) * 25, WIDTH - 23, 1, hulp, top);

    int j;
    for(j = 0; j < 12; j++) {
        draw_square(21, HEIGHT - (20 - j) - (index - 1) * 25, 1, 1, hulp, top);
        draw_square(22, HEIGHT - (20 - j)  - (index - 1) * 25, 1, 1, white, top);

        draw_square(23, HEIGHT - (20 - j)  - (index - 1) * 25, WIDTH - 23, 1, hulp, top);
    }

    draw_square(21, HEIGHT - (19 - j + 1) - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(22, HEIGHT - (19 - j + 1) - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(23, HEIGHT - (19 - j + 1) - (index - 1) * 25, WIDTH - 23, 1, hulp, top);

    draw_square(22, HEIGHT - (18 - j + 1) - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(23, HEIGHT - (18 - j + 1) - (index - 1) * 25, 1, 1, white, top);
    draw_square(24, HEIGHT - (18 - j + 1)  - (index - 1) * 25, WIDTH - 24, 1, hulp, top);

    draw_square(23, HEIGHT - (17 - j + 1) - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(24, HEIGHT - (17 - j + 1) - (index - 1) * 25, 1, 1, white, top);

    draw_square(24, HEIGHT - (16 - j + 1)  - (index - 1) * 25, 1, 1, hulp, top);
    draw_square(25, HEIGHT - (16 - j + 1)  - (index - 1) * 25, 1, 1, white, top);

    draw_square(25, HEIGHT - (17 - j + 1)  - (index - 1) * 25, WIDTH - 25, 1, hulp, top);
    draw_square(25, HEIGHT - (16 - j + 1)  - (index - 1) * 25, WIDTH - 25, 1, white, top);
    draw_square(25, HEIGHT - (15 - j + 1)  - (index - 1) * 25, WIDTH - 25, 1, hulp, top);
  
    //DRAW HERE SOME TEXT ARROUND COORDS (20, 20)
    //IF IT WORKS, TRY THIS TEXT: 
    DrawString(top, messages[messages_count - index].message, 30, HEIGHT - (20 - j)  - (index - 1) * 25 - FONT_SIZE / 2, messages[messages_count - index].color);
}

void printPartOfString(char* message, int index, int length, int x, int y)
{
    if(sizeof(message) - index < length) {
        length = sizeof(message) - index;
    }
    char part[44];
    strncpy(part, message + index, length);
    part[length] = '\0';
    DrawString(top, part, x, y, white);
}

int draw_box3(u8* top, int offset, char *message) {
    char mess[200];
    char part[3][45];
    strcpy(mess, message);
    int lines = (int)(strlen(mess) / 45) + 1;
    mess[strlen(mess)] = '\0';
    if(lines > 3) {
        lines = 3;
    }
    
    int height = 20 * lines;
    Color hulp = background_message;
    if(offset - height > 0) {
        draw_square(25, offset - height, 375, height, hulp, top);
        
        int i, index, length;
        for(i = 0; i < lines; i++) {
            index = 45 * i;
            length = 45;

            if(strlen(mess) - index < length) {
                length = strlen(mess) - index;
            }

            strncpy(part[i], mess + 45 * i, strlen(mess) - 45 * i);
            part[i][length] = '\0';

            DrawString(top, part[i], 28, offset - height + i * 20 + 12, white);
        }
    }
    
    return offset - height - 2;
}
int draw_messages3(u8* top) {
    int offset = HEIGHT - 10;
    
    int i;
    for(i = messages_count; i > 0; i--) {
        if((offset = draw_box3(top, offset, messages[i - 1].message)) < 0) {
            return 0;
        }
    }
    return 0;
}
int draw_box2(u8* top, int index, int offset) {
    //offset is the lowest point we can draw to
    //offset - 10 because we want a space between messages
    struct color hulp;
    if(messages_count - index + 1 == selected_message) {
        hulp = background_message_selected;
    }
    else {
        hulp = background_message;
    }

    //split string if necesairy
    char lines[3][45];
    int linecount = 1;
    int size = sizeof(messages[messages_count - index].message)/sizeof(messages[messages_count - index].message[0]);
    if(size > 44) {
        linecount = 2;
        memcpy(lines[0], messages[messages_count - index].message, 44);
        
        if(size > 88) {
            linecount = 3;
            memcpy(lines[1], messages[messages_count - index].message + 44, 44);
            
            if(size > 132) {
                memcpy(lines[2], messages[messages_count - index].message + 88, 44);
            }
            else {
                memcpy(lines[2], messages[messages_count - index].message + 88, size - 88);
            }
        }
        else {
            memcpy(lines[1], messages[messages_count - index].message + 44, size - 44);
        }
    }
    else {
        memcpy(lines[0], messages[messages_count - index].message, size);
    }
    
    
    draw_square(25, offset - 25, WIDTH - 25, 1, hulp, top);
    draw_square(25, offset - 24, WIDTH - 25, 1, white, top);
    draw_square(25, offset - 23, WIDTH - 25, 1, hulp, top);

    draw_square(24, offset - 24, 1, 1, hulp, top);
    draw_square(25, offset - 24, 1, 1, white, top);

    draw_square(23, offset - 23, 1, 1, hulp, top);
    draw_square(24, offset - 23, 1, 1, white, top);

    draw_square(22, offset - 22, 1, 1, hulp, top);
    draw_square(23, offset - 22, 1, 1, white, top);
    draw_square(24, offset - 22, WIDTH - 24, 1, hulp, top);

    draw_square(21, offset - 21, 1, 1, hulp, top);
    draw_square(22, offset - 21, 1, 1, white, top);
    draw_square(23, offset - 21, WIDTH - 23, 1, hulp, top);
     
    int j;
    for(j = 0; j < 15 * linecount; j++) {
        draw_square(21, offset - (20 - j), 1, 1, hulp, top);
        draw_square(22, offset - (20 - j), 1, 1, white, top);

        draw_square(23, offset - (20 - j), WIDTH - 23, 1, hulp, top);
    }
    
    draw_square(21, offset - (19 - j + 1), 1, 1, hulp, top);
    draw_square(22, offset - (19 - j + 1), 1, 1, hulp, top);
    draw_square(23, offset - (19 - j + 1), WIDTH - 23, 1, hulp, top);

    draw_square(22, offset - (18 - j + 1), 1, 1, hulp, top);
    draw_square(23, offset - (18 - j + 1), 1, 1, white, top);
    draw_square(24, offset - (18 - j + 1), WIDTH - 24, 1, hulp, top);

    draw_square(23, offset - (17 - j + 1), 1, 1, hulp, top);
    draw_square(24, offset - (17 - j + 1), 1, 1, white, top);

    draw_square(24, offset - (16 - j + 1), 1, 1, hulp, top);
    draw_square(25, offset - (16 - j + 1), 1, 1, white, top);

    draw_square(25, offset - (17 - j + 1), WIDTH - 25, 1, hulp, top);
    draw_square(25, offset - (16 - j + 1), WIDTH - 25, 1, white, top);
    draw_square(25, offset - (15 - j + 1), WIDTH - 25, 1, hulp, top);
     
    int i;
    for(i = 0; i < linecount; i++) {
        DrawString(top, lines[i], 30, offset - (20 - 15 * i - 3) - FONT_SIZE / 2, messages[messages_count - index].color);
    }
    return offset - (15 - j + 1);
}
int draw_messages2(u8* top) {
    int offset = HEIGHT - 10;
    
    int i;
    for(i = 0; i < messages_count; i++) {
        if((offset = draw_box2(top, i, offset)) < 0) {
            return 0;
        }
    }
    return 0;
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
        //if(selected_message < messages_count - 9) {
            //current = messages_count - selected_message;
        //}
        //else {
            messages_start = current - 9;
            current = 9;
        //}
    }
    for(i = current; i > 0 && i > current - 9; i--) { //there only fit 9 messages maximum on the screen
        draw_box(top, i);
    }
}

void messages_reset_change() {
    change = false;
}

bool messages_get_change() {
    return change;
}