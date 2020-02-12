#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "signatures.h"

#define LONGUEUR_ADRESSE     16
#define LONGUEUR_MESSAGE    121

typedef struct
{
    char adresse[LONGUEUR_ADRESSE];
    char message[LONGUEUR_MESSAGE];
} Packet;

void handlePacket(Packet *p, const char *ip)
{
    // char buffer[LONGUEUR_MESSAGE];

    // it's for me!!!!!! i'm hyped lmao
    if (strcmp(ip, p->adresse) == 0)
    {
        printf("Je suis le destinataire.\n");
        printf("Le message qui m'est destine : %s\n\n", p->message);
    }
    else
    {
        printf("Je ne suis pas le destinataire.\n");
        printf("Message pour %s : %s\n\n", p->adresse, p->message);
    }
}

int main(int argc, char **argv)
{
    /*
        prgm    [mon ip] [port écoute] [ip suivant] [port envoie]
        prgm   127.0.0.1       1111    127.0.0.2          2222
    */

    char* ip = (char*) malloc(sizeof(char) * strlen(argv[1]));
    strcpy(ip, argv[1]);

    int port = (int) atoi(argv[2]);

    char* ip_neigh = (char*) malloc(sizeof(char) * strlen(argv[3]));
    strcpy(ip_neigh, argv[3]);

    int port_neigh = (int) atoi(argv[4]);

    // data to create sockets

    int fd_send = client(ip_neigh, port_neigh);
    int fd_recv = server(port);
    char buffer[sizeof(Packet)];
    Packet p;

    printf("Press d to begin...\n");
    while (getchar() != 'd');

    do
    {
        // reset buffer
        memset(buffer, '\0', sizeof(char) * sizeof(Packet));
        // recv packet and process it
        receive(fd_recv, buffer, sizeof(Packet));
        sscanf(buffer, "%15s%120s", &p.adresse, &p.message);
        handlePacket(&p, ip);
        // send it to the next dude on the loop
        send_data(fd_send, buffer, sizeof(Packet));
    } while (1);

    return 0;
}

