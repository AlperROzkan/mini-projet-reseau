#include <sys/unistd.h>
#include <network/signatures.h>

int receive(int prise, char *buffer, size_t taille)
{
    return (read(prise, buffer, taille) >= 0) ? 0 : -1;
}