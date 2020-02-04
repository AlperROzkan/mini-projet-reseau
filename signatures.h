#ifndef SIGNATURES_H
#define SIGNATURES_H

#include <sys/types.h>

/**
 * @brief creePriseemission
 * 
 * @param server 
 * @param port 
 * @return int 
 */
int client(char *server, int port);

/**
 * @brief C'est la Prise de Reception. Elle ecoute ce que le client dit.
 * 
 * 
 * @param port 
 * @return int 
 */
int serveur(int port);

/**
 * @brief 
 * 
 * @param prise 
 * @param buffer 
 * @param taille 
 * @return int 
 */
int envoyer(int prise, char *buffer, size_t taille);

/**
 * @brief 
 * 
 * @param prise 
 * @param buffer 
 * @param taille 
 * @return int 
 */
int recevoir(int prise, char *buffer, size_t taille);

#endif