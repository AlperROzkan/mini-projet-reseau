#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "signatures.h"

#define LONGUEUR_ADRESSE     16
#define LONGUEUR_MESSAGE    121

#include <unistd.h>
#include <termios.h>

char getch()
{
    char buf = 0;
    struct termios old = {0};

    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    return buf;
}

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

    printf("%d %d", strcmp(ip, "127.0.0.1"), sizeof(Packet));

    // data to create sockets

    int fd_send = client(ip_neigh, port_neigh);
    int fd_recv = server(port);
    char buffer[sizeof(Packet)];
    Packet p;

    printf("Press d to begin...\n");
    while (1)
    {
        char c = getch();
        if (c == 'd')
            break;
    }

    printf("Starting...\n"); fflush(stdout);

    if (strcmp(ip, "127.0.0.1") == 0)
    {
        printf("I'm sending the first packet\n"); fflush(stdout);
        send_data(fd_send, buffer, sizeof(Packet));
        printf("Packet sent\n"); fflush(stdout);
    }

    printf("Starting again because that's cool\n"); fflush(stdout);

    do
    {
        // reset buffer
        memset(buffer, '\0', sizeof(char) * sizeof(Packet));
        // recv packet and process it
        printf("Trying to receive...\n"); fflush(stdout);
        receive(fd_recv, buffer, sizeof(Packet));
        printf("OMG DUDE that was so hard\n"); fflush(stdout);
        sscanf(buffer, "%15s%120s", &p.adresse, &p.message);
        printf("Gotta process that shit\n"); fflush(stdout);
        handlePacket(&p, ip);
        printf("Shit got processed\n"); fflush(stdout);

        // faking a process time because that's so cool
        sleep(1);  // sleep for 1 SECOND

        // send it to the next dude on the loop
        printf("Sending the shit to space\n"); fflush(stdout);
        send_data(fd_send, buffer, sizeof(Packet));
        printf("Shit got launched into cyber space\n"); fflush(stdout);
    } while (1);

    return 0;
}

