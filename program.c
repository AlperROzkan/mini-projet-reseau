#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "signatures.h"
#include "getch.h"
#include "sleep.h"
#include "defines.h"

#define ADDR_LEN            1  // as bytes
#define MSG_LEN           121
#define MASTER_IP "127.0.0.1"

typedef struct
{
    // 1:token 2:message 3:ack
    int type;

    char  src_addr[ADDR_LEN];
    char dest_addr[ADDR_LEN];

    char message[MSG_LEN];
} Packet;

enum Type
{
    TOKEN = 1,
    MESSAGE = 2,
    ACKNOWLEDGE = 3
};

/**
* Building the buffer (raw data to send over the network) from a packet
*/
void buildBufferFromPacket(char *buffer, Packet *p)
{
    // first put the type
    int i = 0;
    buffer[i] = (char) p->type;  // explicit cast to a smaller type to avoid compiler warning on precision loss
    i++;

    // then copy the addresses and message with an offset
    for (int c = i; i - c < ADDR_LEN; ++i)
        buffer[i] = p->src_addr[i - c];

    for (int c = i; i - c < ADDR_LEN; ++i)
        buffer[i] = p->dest_addr[i - c];

    for (int c = i; i - c < MSG_LEN; ++i)
        buffer[i] = p->message[i - c];
}

/**
* Building the packet structure from the buffer data
*/
void buildPacketFromBuffer(Packet *p, char *buffer)
{
    int i = 0;
    p->type = buffer[i];  // the number was directly stored into the first byte
    i++;

    for (int c = i; i - c < ADDR_LEN; ++i)
        p->src_addr[i - c] = buffer[i];

    for (int c = i; i - c < ADDR_LEN; ++i)
        p->dest_addr[i - c] = buffer[i];

    for (int c = i; i - c < MSG_LEN; ++i)
        p->message[i - c] = buffer[i];
}

/**
* Building a token packet and putting it into the buffer
*/
void buildBufferAsToken(char *buffer, Packet *p)
{
    // change type, set source and dest as magic address 0xff * ADDR_LEN
    p->type = TOKEN;
    memset(p->src_addr,  0xff, sizeof(char) * ADDR_LEN);
    memset(p->dest_addr, 0xff, sizeof(char) * ADDR_LEN);
    bzero(p->message, sizeof(char) * MSG_LEN);

    buildBufferFromPacket(buffer, p);
}

void handlePacket(char *buffer, Packet *p, const char *ip)
{
    // do different things based on the type of the packet
    switch (p->type)
    {
        case TOKEN:
            if (1) //wannaSend())
            {
                // je prends le token 
                printf("je veux parler, je prends le token\n");
                // takeToken();
                printf("j'ai pris le token\n");
            }
            else
            {
                // forward du token
                printf("je ne veux pas parler je forward le token");
            }
            break;
        
        case MESSAGE:
            if (strcmp(ip, p->dest_addr) == 0)
            {
                printf("Je suis le destinataire.\n");
                printf("Le message qui m'est destine : %s\n\n", p->message);
                printf("Je renvoie l'ACK");
                // EnvoieACK();
                printf("J'ai envoyé l'ACK");
            }
            else
            {
                printf("Je ne suis pas le destinataire.\n");
                printf("Message pour %s : %s\n\n", p->dest_addr, p->message);
            }
            break;
        
        case ACKNOWLEDGE:
            if (1) //attenteACK())
            {
                printf("J'ai recu l'ack que j'attendais.\n");
                printf("Je release le token");
                // releaseToken();
            }
            else
            {
                // forward de l'ack
                printf("Je ne suis pas le destinataire.\n");
            }
            break;
        
        default:
            printf("wtf bro !?\n");
            break;
    }
}

int main(int argc, char **argv)
{
    /*
        prgm    [my ip] [listenning port] [neighbor ip] [destination port]
        prgm  127.0.0.1              1111     127.0.0.2               2222
    */

    if (argc != 5)
    {
        printf("Need 4 arguments:\n\t%s [my ip] [listenning port] [neighbor ip] [destination port]\n", argv[0]);
        printf("Example:\n\t%s 127.0.0.1 1111 127.0.0.2 2222\n", argv[0]);
        return EXIT_FAILURE;
    }

    // reading arguments
    char* ip = (char*) malloc(sizeof(char) * strlen(argv[1]));
    strcpy(ip, argv[1]);
    int port = (int) atoi(argv[2]);
    char* ip_neigh = (char*) malloc(sizeof(char) * strlen(argv[3]));
    strcpy(ip_neigh, argv[3]);
    int port_neigh = (int) atoi(argv[4]);

    // data to create sockets
    int fd_send = client(ip_neigh, port_neigh);
    int fd_recv = server(port);

    // buffer to store bytes to send (raw data)
    char buffer[sizeof(Packet)];
    // structure to store formatted data about the packet
    Packet p;

    // waiting for user input before starting
    printf("Press d to begin...\n");
    while (1)
    {
        char c = getch();
        if (c == 'd')
            break;
    }

    printf("Starting...\n"); fflush(stdout); // flush force le réaffichage vers le stdout

    // send first packet if we are the master
    if (strcmp(ip, MASTER_IP) == 0)
    {
        printf("Sending first packet... "); fflush(stdout);
        buildBufferAsToken(buffer, &p);
        send_data(fd_send, buffer, sizeof(Packet));
        msleep(555);
        printf("done\n"); fflush(stdout);
    }

    do
    {
        // reset buffer
        bzero(buffer, sizeof(char) * sizeof(Packet));

        // recv packet and process it
        receive(fd_recv, buffer, sizeof(Packet));
        buildPacketFromBuffer(&p, buffer);

        // process packet data, knowing what is our own IP
        handlePacket(buffer, &p, ip);

        // faking a process time because that's so cool
        msleep(555);  // sleep for 555ms

        // send it to the next dude on the loop
        send_data(fd_send, buffer, sizeof(Packet));
    } while (1);

    return EXIT_SUCCESS;
}

