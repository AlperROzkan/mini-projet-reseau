#ifndef SIGNATURES_H
#define SIGNATURES_H

#include <sys/types.h>

/**
 * @brief create file descriptor for client
 * 
 * @param server 
 * @param port 
 * @return int 
 */
int client(char *server, int port);

/**
 * @brief create file descriptor for server
 * 
 * 
 * @param port 
 * @return int 
 */
int server(int port);

/**
 * @brief 
 * 
 * @param fd 
 * @param buffer 
 * @param size 
 * @return int 
 */
int send_data(int fd, char *buffer, size_t size);

/**
 * @brief 
 * 
 * @param fd 
 * @param buffer 
 * @param size 
 * @return int 
 */
int receive(int fd, char *buffer, size_t size);

#endif