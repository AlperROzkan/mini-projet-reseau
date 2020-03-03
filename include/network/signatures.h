#ifndef SIGNATURES_H
#define SIGNATURES_H

#include <sys/types.h>

/**
 * @brief Create file descriptor for client.
 * 
 * @param server 
 * @param port 
 * @return int 
 */
int client(char *server, int port);

/**
 * @brief Create file descriptor for server.
 * 
 * 
 * @param port 
 * @return int 
 */
int server(int port);

/**
 * @brief Send buffer to data descriptor.
 * 
 * @param fd 
 * @param buffer 
 * @param size 
 * @return int 
 */
int send_data(int fd, char *buffer, size_t size);

/**
 * @brief Receive buffer from data descriptor.
 * 
 * @param fd 
 * @param buffer 
 * @param size 
 * @return int 
 */
int receive(int fd, char *buffer, size_t size);

#endif