#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#include "signatures.h"

int server(int port)
{
    int sock;
    struct sockaddr_in address;

    /*
    *   create socket (server), only receiving data
    */
   if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("server: couldn't create socket");
        exit(1);
    }

    /*
    *   bind udp socket
    */
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*) &address, sizeof(address)) == -1)
    {
        perror("server: coudln't bind socket");
        exit(1);
    }

    return sock;
}