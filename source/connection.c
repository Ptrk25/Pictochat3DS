#include <3ds.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <errno.h>

#include "connection.h"
#include "color.h"
#include "messages.h"



static void *SOC_buffer = NULL;
static int chatls = -1;

#define STACKSIZE (4 * 1024)

void get_mac() {
    
}

int con_init(void) {
    SOC_buffer = memalign(0x1000, 0x100000);
    if(SOC_buffer == NULL)
        return -1;

    Result ret = SOC_Initialize(SOC_buffer, 0x100000);
    if(ret != 0)
    {
        // need to free the shared memory block if something goes wrong
        SOC_Shutdown();
        free(SOC_buffer);
        SOC_buffer = NULL;
        return -1;
    }
    return 0;
}

int con_dinit(void) {
    //exitReceive = true;
    
    //svcSleepThread(100000000ULL);
    
    if(chatls >= 0) {
        closesocket(chatls);
        chatls = -1;
    }
    
    Result ret = SOC_Shutdown();
    
    if(ret < 0) {
        return -1;
    }
    return 0;
}
void sock_send(char* message, size_t size) {
    int n = sendto(chatls, message, size, 0, NULL, 0);
    if (n == -1)
    {
       add_message("ERROR writing to socket", 1, white, background_message);
    }
}

static int set_socket_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL);

    if(flags == -1) return -1;

    int rc = fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    if(rc != 0) return -1;

    return 0;
}

static int sock_receive(char* message, size_t size) {
    int len;
    len = recv(chatls, message, size, 0);
     
    if (len == -1) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            return -1;
        }
    }
    return len;
}
void get_message() {
    char message[500] = "";
    int n = sock_receive(message, 500);
    if(n > 0) {
        //printf("%i%s\n", n, message);
        add_message(message, 1, white, background_message);
    }
    else {
        //connection lost
        
    }
}

int con_activate(void) {
    int n;
    struct sockaddr_in serv_addr;
    
    //initialise shit
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("176.31.170.43");
    serv_addr.sin_port = htons(9125);

    // create listening socket on all addresses on NETLOADER_PORT
    chatls = socket(AF_INET, SOCK_STREAM, 0);
    if(chatls < 0)
    {
        //printf("Error opening socket\n");
        return -1;
    }
    n = connect(chatls, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (n < 0)
    {
       //printf("ERROR connecting\n");
       return -2;
    }
    if(set_socket_nonblocking(chatls) == -1) {
        //add_message("Nonblocking failed", 1, white, background_message);
        return -3;
    }
    //add_message("Ready", 1, white, background_message);
    
    //printf("Threads ready\n");
    //signal_receive();
    //get_message();
    //printf("Threads booted\n");
    
    return 0;
}