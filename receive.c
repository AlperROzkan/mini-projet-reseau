#include <sys/unistd.h>
#include "signatures.h"

int receive(int prise, char *buffer, size_t taille)
{
    return (read(prise, buffer, taille) >= 0) ? 0 : -1;
}