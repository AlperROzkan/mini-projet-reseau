#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>  // for bzero

#include "signatures.h"
#include "getch.h"
#include "sleep.h"

#define ADDR_LEN     16
#define MSG_LEN     121
#define MASTER_IP "127.0.0.1"

typedef struct
{
    char address[ADDR_LEN];
    char message[MSG_LEN];
} Packet;

/**
* Building a token packet and putting it into the buffer
*/
void buildBufferAsToken(char *buffer, Packet *p)
{}

/**
* building the buffer (raw data to send over the network) from a packet
*/
void buildBufferFromPacket(char *buffer, Packet *p)
{
    int i = 0;
    for (; i < ADDR_LEN; ++i)
        buffer[i] = p->address[i];
    
    const int last = i;

    for (; i - last < MSG_LEN; ++i)
        buffer[i] = p->message[i - last];
}

/**
* Building the packet structure from the buffer data
*/
void buildPacketFromBuffer(Packet *p, char *buffer)
{
    int i = 0;
    for (; i < ADDR_LEN; ++i)
        p->address[i] = buffer[i];
    
    const int last = i;

    for (; i - last < MSG_LEN; ++i)
        p->message[i - last] = buffer[i];
}

void handlePacket(Packet *p, const char *ip)
{
    // checking if the packet is for us
    if (strcmp(ip, p->address) == 0)
    {
        printf("I got a message... ");
        msleep(222);
        printf("%s\n\n", p->message);
    }
    else
    {
        printf("This isn't for me... ");
        msleep(333);
        printf("for %s : %s\n\n", p->address, p->message);
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
    char buffer[sizeof(Packet)];
    Packet p;

    // waiting for user input before starting
    printf("Press d to begin...\n");
    while (1)
    {
        char c = getch();
        if (c == 'd')
            break;
    }

    printf("Starting...\n"); fflush(stdout);

    // send first packet if we are the master
    if (strcmp(ip, MASTER_IP) == 0)
    {
        printf("Sending first packet... "); fflush(stdout);
        buildBufferAsToken(buffer, &p);
        send_data(fd_send, buffer, sizeof(Packet));
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
        handlePacket(&p, ip);

        // faking a process time because that's so cool
        sleep(1);  // sleep for 1 SECOND

        // send it to the next dude on the loop
        send_data(fd_send, buffer, sizeof(Packet));
    } while (1);

    return 0;
}

