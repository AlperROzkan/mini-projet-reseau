#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <network/signatures.h>
#include <utils/getch.h>
#include <utils/sleep.h>
#include <utils/defines.h>
#include <utils/messages.h>
#include <packet.h>
#include <utils/colors.h>

int main(int argc, char **argv)
{
    FILE *fp;
    if((fp = fopen("../build/messagesMaster.txt", "r+"))==NULL) {
        perror("Error while opening file.");
        exit(EXIT_FAILURE);
    }


    /*
        prgm    [my ip] [listenning port] [neighbor ip] [destination port]
        prgm  127.0.0.1              1111     127.0.0.2               2222
    

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

    Data data;
    data.waiting_for_ack = 0;
    data.message_count = 0;
    data.messages = (MsgData*) calloc(MAX_MESSAGES, sizeof(MsgData));

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
        printf(ANSI_COLOR_CYAN "Sending first packet... " ANSI_COLOR_RESET);
        fflush(stdout);

        buildBufferAsToken(buffer, &p);

        send_data(fd_send, buffer, sizeof(Packet));

        printf(ANSI_COLOR_GREEN "done\n" ANSI_COLOR_RESET); fflush(stdout);

        data.message_count = 2;
            sprintf(data.messages[0].message, "%s", "first message");
            sprintf(data.messages[0].addr,    "%s", "127.000.000.002");
        sprintf(data.messages[1].message, "%s", "second message");
        sprintf(data.messages[1].addr,    "%s", "127.000.000.003");
    }

    do
    {
        // reset buffer
        bzero(buffer, sizeof(char) * sizeof(Packet));

        // recv packet and process it
        receive(fd_recv, buffer, sizeof(Packet));
        buildPacketFromBuffer(&p, buffer);

        printf(
            "("
            ANSI_COLOR_YELLOW "%d" ANSI_COLOR_RESET
            ") ["
            ANSI_COLOR_BLUE "%s -> %s" ANSI_COLOR_RESET
            "] "
            ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET
            , p.type, p.src_addr, p.dest_addr, p.message);

        // process packet data, knowing what is our own IP
        handlePacket(buffer, &p, ip, &data);

        // faking a process time because that's so cool
        msleep(555);  // sleep for 555ms

        // send it to the next dude on the loop
        send_data(fd_send, buffer, sizeof(Packet));
        //printf("\t\tdone\n");

        if (data.message_count == 0)
            printf(ANSI_COLOR_CYAN "I have no more messages\n" ANSI_COLOR_RESET);
    } while (1);

    free(data.messages);

    return EXIT_SUCCESS;*/
}

