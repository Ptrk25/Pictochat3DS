/* 
 * File:   connection.h
 * Author: bert
 *
 * Created on 30 juli 2015, 18:06
 */

#ifndef CONNECTION_H
#define	CONNECTION_H

int con_init(void);
int con_dinit(void);
int con_activate(void);
void get_message();
void sock_send(char* message, size_t size);

#endif
