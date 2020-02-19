#ifndef packet_h
#define packet_h

#include <utils/defines.h>

enum Type  // Message types
{
    TOKEN = 1,
    MESSAGE = 2,
    ACKNOWLEDGE = 3
};

typedef struct  // used to store the packet data
{
    char type;

    char  src_addr[ADDR_LEN];
    char dest_addr[ADDR_LEN];

    char message[MSG_LEN];
} Packet;

#define MAX_MESSAGES 64

typedef struct
{
    char message[MSG_LEN];
    char addr[ADDR_LEN];
    int ack;
} MsgData;

typedef struct
{
    int waiting_for_ack;

    MsgData *messages;
    int message_count;
} Data;

void buildBufferFromPacket(char *buffer, Packet *p);
void buildPacketFromBuffer(Packet *p, char *buffer);
void buildBufferAsToken(char *buffer, Packet *p);
void handlePacket(char *buffer, Packet *p, const char *ip, Data *data);

#endif  // packet_h