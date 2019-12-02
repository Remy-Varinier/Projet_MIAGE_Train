#define MAX 100
#define PORT 7780

#ifndef RESEAU_H
#define RESEAU_H
int socketClient(char nomServeur[], int port);
int socketServeur(int port);
#endif
