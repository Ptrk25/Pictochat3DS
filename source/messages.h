/* 
 * File:   messages.h
 * Author: bert
 *
 * Created on 21 juli 2015, 19:18
 */
#pragma once

#ifndef MESSAGES_H
#define	MESSAGES_H



void init_messages();
void add_message(char* message, int sender, Color color);
void selection_up();
void selection_down();
void draw_messages();

#endif

