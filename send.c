#include <sys/unistd.h>
#include "signatures.h"

int send_data(int fd, char *buffer, size_t taille)
{
    return (write(fd, buffer, taille) == taille) ? 0 : -1;
}