/* 
 * File:   messages.h
 * Author: Bert Bijnens
 *
 * Created on 21 juli 2015, 19:18
 */
#pragma once

#ifndef MESSAGES_H
#define	MESSAGES_H

typedef struct message {
    char message[41];
    int sender;
    Color color;
    Color bgcolor;
}Message;

/**
 * Initialises the necesairy variables to make use of the other functions
 */
void init_messages();

/**
 * Draws a rectangle in the given color
 * 
 * @param message The message
 * @param sender The unique id of the sender
 * @param color Textcolor in the Color format
 * @param bgcolor Backgroundcolor in the Color format
 */
void add_message(char* message, int sender, Color color, Color bgcolor);

/**
 * Changes the selection of the message to the one above
 */
void selection_up();

/**
 * Changes the selection of the message to the one below
 */
void selection_down();

/**
 * Draws each message to the top screen
 */
void draw_messages();

void messages_reset_change();

bool messages_get_change();

#endif

