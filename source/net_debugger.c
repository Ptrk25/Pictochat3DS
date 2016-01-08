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

static void *SOC_buffer = NULL;
static int netls = -1;

int nd_set_socket_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL);

    if(flags == -1) return -1;

    int rc = fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    if(rc != 0) return -1;

    return 0;
}

int nd_activate(void) {
    int n;
    struct sockaddr_in serv_addr;
    
    //initialise shit
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.7");
    serv_addr.sin_port = htons(9140);

    netls = socket(AF_INET, SOCK_STREAM, 0);
    if(netls < 0)
    {
        return -1;
    }
    n = connect(netls, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (n < 0)
    {
       return -2;
    }
    if(nd_set_socket_nonblocking(netls) == -1) {
        return -3;
    }
    return 0;
}

int ndInit(void) {
    //SOC_buffer = memalign(0x1000, 0x100000);
    //if(SOC_buffer == NULL)
        //return -1;

    nd_activate();
    
    Result ret = 0; //SOC_Initialize(SOC_buffer, 0x100000);
    if(ret != 0)
    {
        SOC_Shutdown();
        free(SOC_buffer);
        SOC_buffer = NULL;
        return -1;
    }
    
    return 0;
}

int ndExit(void) {
    if(netls >= 0) {
        closesocket(netls);
        netls = -1;
    }
    
    Result ret = SOC_Shutdown();
    
    if(ret < 0) {
        return -1;
    }
    return 0;
}
void nd_sock_send(char* message, size_t size) {
    sendto(netls, message, size, 0, NULL, 0);
}

void nd_print(char *message) {
    nd_sock_send(message, sizeof(message));
}