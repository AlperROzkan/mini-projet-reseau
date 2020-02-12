#include <stdio.h>
#include <netdb.h>      // socket, connect
#include <arpa/inet.h>  // sockaddr_in
#include <stdlib.h>

#include "signatures.h"
#include <string.h>     // memset

int client(char *server, int port)
{
    int sock;
    struct sockaddr_in address;

    /* 
    *   creating udp socket
    */ 
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("client: couldn't create socket");
        exit(1);
    }

    /*
    *   creating socket structure
    */ 
    memset(&address, 0, sizeof(address));
    memcpy(&address.sin_addr, server, strlen(server));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    
    if (connect(sock, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1)
    {
        perror("client: couldn't connect socket");
        exit(1);
    }

    return sock;
}