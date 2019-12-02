#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/uio.h>

#define MAX 256               /* Nombre maximum de caractères lus */
#define MAX_CAR 256		      /* Nombre maximum de caractères possible*/

struct train{ 
	int num_train;            /* numéro du train */
	char ville_dep[MAX_CAR];  /* ville de départ */
	char ville_arr[MAX_CAR];  /* ville d'arrivée */
	struct horaire h_depart;  /* heure de départ */
	struct horaire h_arrivee; /* heure d'arrivée */
	float prix;               /* prix usuel */
	char option[5]            /* champ optionnel:
								 REDUC si le train bénéficie d'une remise de 20%
								 SUPPL si le train fait l'objet d'un supplément de 10%
							   */
};

struct horaire{
	short heure; 
	short minute; 
};

int main(int argc,char *argv[]){ 
	/*int ecoute = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(7777);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(ecoute, (struct sockaddr *)&sin, sizeof(sin));
	listen(ecoute,5);//écoute de la socket*/
	int ecoute = socketServeur("localhost",4242);
	int echange = accept(ecoute,NULL, NULL);
	printf("Un client s'est connecté \n");
	char tampon[MAX];
	read(ecoute, tampon, sizeof(ecoute));
	printf("Un client est connecté \n");
	return 0;
}
