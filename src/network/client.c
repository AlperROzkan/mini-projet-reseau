#include <stdio.h>
#include <netdb.h>      // socket, connect
#include <arpa/inet.h>  // sockaddr_in
#include <stdlib.h>
#include <string.h>     // memset

#include <network/signatures.h>
#include <utils/defines.h>

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
    bzero((char*) &address, sizeof(struct sockaddr_in));
    address.sin_addr.s_addr = inet_addr(server);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    
    if (connect(sock, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1)
    {
        perror("client: couldn't connect socket");
        exit(1);
    }

    return sock;
}