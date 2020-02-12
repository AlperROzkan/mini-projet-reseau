#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "signatures.h"
#include "getch.h"
#include "sleep.h"
#include "defines.h"

// small trick using a function and a static value to store a global value safely
int setWaitingForAck(int val)
{
    static int b = 0;  // not waiting for an ack
    if (val == 0 || val == 1)
        b = val;
    return b;
}

int hasMessage(int i)
{
    static int m = 2;
    if (i == 1)
        m--;
    if (m >= 0)
        return 1;
    return 0;
}

enum Type
{
    TOKEN = 1,
    MESSAGE = 2,
    ACKNOWLEDGE = 3
};

typedef struct
{
    char type;

    char  src_addr[ADDR_LEN];
    char dest_addr[ADDR_LEN];

    char message[MSG_LEN];
} Packet;

/**
* Building the buffer (raw data to send over the network) from a packet
*/
void buildBufferFromPacket(char *buffer, Packet *p)
{
    // first put the type
    int i = 0;
    buffer[i] = p->type;
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

void writeMessage(Packet *p, const char *ip)
{
    p->type = MESSAGE;
    memcpy(p->src_addr, ip, sizeof(char) * ADDR_LEN);

    memcpy(p->dest_addr, ip, sizeof(char) * ADDR_LEN);
    p->dest_addr[ADDR_LEN - 2] = (((ip[ADDR_LEN - 2] - '0') + 1) % 4) + '1';  // TODO remove, just for tests

    memcpy(p->message, "hello world", 12);
}

void sendAck(Packet *p, const char *ip)
{
    p->type = ACKNOWLEDGE;
    memcpy(p->dest_addr, p->src_addr, sizeof(char) * ADDR_LEN);
    memcpy(p->src_addr, ip, sizeof(char) * ADDR_LEN);
    // leave the message as is
}

void handlePacket(char *buffer, Packet *p, const char *ip)
{
    // do different things based on the type of the packet
    switch (p->type)
    {
        case TOKEN:
            if (hasMessage(1))  // if we have something to say
            {
                printf("\n-> token\t\t");
                writeMessage(p, ip);
                buildBufferFromPacket(buffer, p);
                msleep(444);
                printf("message -> (%s)", p->dest_addr);
            }
            // otherwise, no need to modify the packet, just send the packet as it was received, as a token
            break;
        
        case MESSAGE:
            if (strcmp(ip, p->dest_addr) == 0)
            {
                printf("\n[%s] %s\t\t", p->src_addr, p->message);
                sendAck(p, ip);
                setWaitingForAck(1);
                msleep(444);
                printf("... ACK written from %s to %s", p->src_addr, p->dest_addr);
                buildBufferFromPacket(buffer, p);
            }
            else
            {
                // message isn't for us, no need to display it, only print a dot to say we received something
                printf(".");
            }
            break;
        
        case ACKNOWLEDGE:
            if (setWaitingForAck(-1) == 1)  // arguments different from 0 and 1 do not affect the stored value
            {
                // reset waiting for ack
                setWaitingForAck(0);
                printf("\n-> ACK\t\ttoken ->");
                buildBufferAsToken(buffer, p);
            }
            // otherwise do nothing, the ACK will be forwarded
            break;
        
        default:
            printf("ERROR, I do not know this kind of packet\n");
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

        //printf("(%d) [%s -> %s] %s\n", p.type, p.src_addr, p.dest_addr, p.message);

        // process packet data, knowing what is our own IP
        handlePacket(buffer, &p, ip);

        // faking a process time because that's so cool
        msleep(555);  // sleep for 555ms

        // send it to the next dude on the loop
        send_data(fd_send, buffer, sizeof(Packet));
        //printf("\t\tdone\n");

        if (hasMessage(0) == 0)
            printf("i have no more messages\n");
    } while (1);

    return EXIT_SUCCESS;
}

