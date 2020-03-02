#include <utils/messages.h>
#include <stdio.h>
#include <stdlib.h>

FILE initializeFile(char *charPath) {
    FILE *fp;
    if((fp = fopen(charPath, "r+"))==NULL) {
        perror("Error while opening file.");
        printf("path is %s\n", charPath);
        exit(EXIT_FAILURE);
    }
    printf("nice\n");
}

int readMessage(FILE messageFile)
{
    
}