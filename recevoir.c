#include <sys/unistd.h>
#include "signatures.h"

int recevoir(int prise, char *buffer, size_t taille)
{
    if (read(prise, buffer, taille) >= 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
    
}