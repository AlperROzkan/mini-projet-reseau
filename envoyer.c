#include <sys/unistd.h>

#include "signatures.h"

int envoyer(int prise, char *buffer, size_t taille)
{
    return (write(prise, buffer, taille) == taille) ? 0 : -1;
}