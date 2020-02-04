#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "signature.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */

#define ADRESSE_EMETTEUR	"127.0.0.1"
#define ADRESSE_RECEPTEUR	"127.0.0.1"
#define PORT_RECEPTION		1920
#define PORT_EMISSION		1990
#define LONGUEUR_ADRESSE	16
#define LONGUEUR_MESSAGE	121
//#define LONGUEUR_TYPE       2

typedef struct paquet
{
    //int type;
	//char adresse_Dest[LONGUEUR_ADRESSE];
    //char adresse_Src[LONGUEUR_ADRESSE];
    char adresse[LONGUEUR_ADRESSE];
	char message[LONGUEUR_MESSAGE];
} Paquet;
/* Paquet <=> struct paquet */  

void traitePaquet(Paquet *p)
{
	char buffer[LONGUEUR_MESSAGE];

    //if (type == 1){
        /*le paquet est de type token*/


    //}
    //else if(type == 2){
        /* si le paquet est de type message*/
        if (strcmp(ADRESSE_EMETTEUR, p->adresse) == 0)
        /* si je suis le destinataire du paquet */
        {
            printf("message : ");
            scanf("%s", buffer);
            sprintf(p->message, "%120s", buffer);
            printf("\n");
        }
        else
            /* sinon */
            printf("message de %s : %s\n", p->adresse, p->message);
    //}
}

int main (int argc, char **argv)
{
	int    priseEmission, priseReception;
	//char   buffer[LONGUEUR_TYPE + LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
    char   buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
	Paquet p;

	priseEmission  = client(ADRESSE_RECEPTEUR, PORT_EMISSION); // port d'envoie
	priseReception = serveur(PORT_RECEPTION);   //port de réception

	printf("J'envoie le 1er paquet \n");
	printf("Touche d pour demarrer...\n");
  	while (getchar() != 'd'); /* temporisation */

	sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "blablabla");
	envoyer(priseEmission, buffer, strlen(buffer));
	/* ex. remplissage 1er paquet puis emission */

	printf("PC1 demarre ...\n\n");

	/* boucle en emission */
	do
	{
		printf("Envoyer un autre paquet ? \n");
		printf("Touche e pour continuer...\n");
  		while (getchar() != 'e'); /* temporisation */

		memset (buffer, '\0', sizeof(buffer));

		sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "nouveauBlabla");

		envoyer(priseEmission, buffer, strlen(buffer));

	} while (1); /* boucle infinie */

  return 0;
}
