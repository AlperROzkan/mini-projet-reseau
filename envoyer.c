#include <sys/unistd.h>

#include "signatures.h"

int envoyer(int prise, char *buffer, size_t taille)
{
    if (write(prise, buffer, taille)== taille)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}