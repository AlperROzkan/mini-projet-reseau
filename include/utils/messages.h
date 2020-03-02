#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdio.h>

/**
 * @brief initializes the given file.
 * 
 * @param file 
 * @return int 
 */
FILE initializeFile(char *path);

/**
 * @brief initialize the message file and reads them.
 * 
 * @param messageFile 
 */
int readMessage(FILE messageFile);

#endif