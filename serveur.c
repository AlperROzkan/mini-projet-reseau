#include <stdio.h>
#include <netdb.h>	
#include <arpa/inet.h>  
#include <stdlib.h>	
#include <string.h>	

int serveur(int port)
{
    int			sock;
    struct sockaddr_in	address;

    /*
    *   Creation socket UDP.
    */
   if ((sock = socket (PF_INET, SOCK_DGRAM, 0)) == -1)
    {
	    perror ("creerPriseReception");
    	exit (1);
    }

    /*
    *   Creation structure socket.
    */
    memset (&address, 0, sizeof (address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons (port);

    if (bind (sock,(struct sockaddr*) &address,sizeof (address)) == -1)
    {
        perror ("creerPriseReception");
        exit (1);
    }

    return sock;
}