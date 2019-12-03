#define MAX 100
#define PORT 8000

#ifndef RESEAU_H
#define RESEAU_H
int socketClient(char nomServeur[], int port);
int socketServeur(int port);
#endif
