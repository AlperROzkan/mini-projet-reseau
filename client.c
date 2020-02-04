#include <stdio.h>
#include <netdb.h>	// socket, connect, hostent
#include <arpa/inet.h>  // sockaddr_in
#include <stdlib.h>

#include "signatures.h"	
#include <string.h>	// memset

int client(char *server, int port)
{
    int			sock;
    struct sockaddr_in	address;
    struct hostent     *hp;

    /* 
    *   Creation d'une socket UDP.
    */ 
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("creerPriseEmission");
        exit(1);
    }

    /*
    *   Résolution
    */ 
    hp = gethostbyname(server);
    if (hp == 0)
    {
        perror("creerPriseEmission");
        exit(1);
    }

    /*
    *   Création d'une structure d'adresse socket.
    */ 
    memset(&address, 0, sizeof(address));
    memcpy(&address.sin_addr, hp->h_addr, hp->h_length);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    
    /*
    *   Bloc connect pour sockets UDP qui permet d'afficher l'adresse utilisee lors d'emission avec send.
    */
    if (connect(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
    {
        perror("creerPriseEmission");
        exit(1);
    }

    return sock;
}