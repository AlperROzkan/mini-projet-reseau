#include <packet.h>
#include <stdio.h>
#include <string.h>

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

void writeMessage(Packet *p, const char *msg, const char *to, const char *ip)
{
    p->type = MESSAGE;

    memset(p->src_addr, 0, ADDR_LEN);
    memcpy(p->src_addr, ip, sizeof(char) * ADDR_LEN);

    memset(p->dest_addr, 0, ADDR_LEN);
    memcpy(p->dest_addr, to, sizeof(char) * ADDR_LEN);

    memset(p->message, 0, MSG_LEN);
    memcpy(p->message, msg, strlen(msg));
}

void sendAck(Packet *p, const char *ip)
{
    p->type = ACKNOWLEDGE;
    memcpy(p->dest_addr, p->src_addr, sizeof(char) * ADDR_LEN);
    memcpy(p->src_addr, ip, sizeof(char) * ADDR_LEN);
    // leave the message as is
}

void handlePacket(char *buffer, Packet *p, const char *ip, Data *data)
{
    // do different things based on the type of the packet
    switch (p->type)
    {
        case TOKEN:
            if (data->message_count > 0)  // if we have something to say
            {
                printf("\n-> token\t\t");
                int i = data->message_count;
                writeMessage(p, data->messages[i - 1].message, data->messages[i - 1].addr, ip);
                data->message_count--;
                buildBufferFromPacket(buffer, p);
                printf("message -> (%s)", p->dest_addr);
            }
            // otherwise, no need to modify the packet, just send the packet as it was received, as a token
            break;
        
        case MESSAGE:
            if (strcmp(ip, p->dest_addr) == 0)
            {
                printf("\n[%s] %s\t\t", p->src_addr, p->message);
                sendAck(p, ip);
                data->waiting_for_ack = 1;
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
            if (data->waiting_for_ack)  // arguments different from 0 and 1 do not affect the stored value
            {
                // reset waiting for ack
                data->waiting_for_ack = 0;
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